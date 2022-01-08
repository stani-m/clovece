#include <cstdio>
#include <raylib.h>
#include "server/Game.h"
#include "client/Client.h"
#include <pthread.h>

const int PORT = 1234;

typedef struct Data {
    int numberOfPlayers;
    std::string serverAddress;
    pthread_mutex_t *mutex;
    bool serverStarted;
    pthread_cond_t *serverStartedCond;
} Data;

void *serverThread(void *arg) {
    auto *data = static_cast<Data *>(arg);

    SetRandomSeed(time(nullptr));

    Game game(PORT);
    game.startListening();

    pthread_mutex_lock(data->mutex);
    data->serverStarted = true;
    pthread_mutex_unlock(data->mutex);
    pthread_cond_broadcast(data->serverStartedCond);

    game.startGame(data->numberOfPlayers);

    return nullptr;
}

int main(int argn, char *argv[]) {
    if (argn < 3) {
        fprintf(stderr, "incorrect number of arguments\n");
        return 1;
    }

    SetTraceLogLevel(LOG_WARNING);

    if (std::string(argv[1]) == "start") {
        int numberOfPlayers = std::stoi(argv[2]);
        if(numberOfPlayers < 1 || numberOfPlayers > 4) {
            fprintf(stderr, "incorrect number of players\n");
            return 1;
        }
        pthread_t server;

        pthread_mutex_t mutex;
        pthread_cond_t serverStartedCond;

        pthread_mutex_init(&mutex, nullptr);
        pthread_cond_init(&serverStartedCond, nullptr);

        Data data{
                .numberOfPlayers = std::stoi(argv[2]),
                .serverAddress = "localhost",
                .mutex = &mutex,
                .serverStarted = false,
                .serverStartedCond = &serverStartedCond
        };

        pthread_create(&server, nullptr, &serverThread, &data);

        pthread_mutex_lock(data.mutex);
        while (!data.serverStarted) {
            pthread_cond_wait(data.serverStartedCond, data.mutex);
        }
        Client client(data.serverAddress, PORT);
        pthread_mutex_unlock(data.mutex);

        client.start();

        pthread_join(server, nullptr);

        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&serverStartedCond);
    } else if (std::string(argv[1]) == "connect") {
        Client client(std::string(argv[2]), PORT);
        client.start();
    } else {
        fprintf(stderr,"Invalid first argument. Only valid options are start/connect.\n");
        return 1;
    }

    return 0;
}
