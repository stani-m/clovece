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
    pthread_cond_signal(data->serverStartedCond);

    game.startGame(data->numberOfPlayers);

    return nullptr;
}

void *clientThread(void *arg) {
    auto *data = static_cast<Data *>(arg);

    pthread_mutex_lock(data->mutex);
    while (!data->serverStarted) {
        pthread_cond_wait(data->serverStartedCond, data->mutex);
    }
    Client client(data->serverAddress, PORT);
    pthread_mutex_unlock(data->mutex);

    client.start();

    return nullptr;
}

int main(int argn, char *argv[]) {
    if (argn < 3) {
        fprintf(stderr, "incorrect number of arguments\n");
        return 1;
    }

    SetTraceLogLevel(LOG_WARNING);

    if (std::string(argv[1]) == "start") {
        pthread_t server, client;

        pthread_mutex_t mutex;
        pthread_cond_t serverStartedCond;

        pthread_mutex_init(&mutex, nullptr);
        pthread_cond_init(&serverStartedCond, nullptr);

        Data data{
                .numberOfPlayers = atoi(argv[2]),
                .serverAddress = "localhost",
                .mutex = &mutex,
                .serverStarted = false,
                .serverStartedCond = &serverStartedCond
        };

        pthread_create(&server, nullptr, &serverThread, &data);
        pthread_create(&client, nullptr, &clientThread, &data);

        pthread_join(client, nullptr);
        pthread_join(server, nullptr);

        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&serverStartedCond);
    } else if (std::string(argv[1]) == "connect") {
        pthread_t client;

        pthread_mutex_t mutex;
        pthread_cond_t serverStartedCond;

        pthread_mutex_init(&mutex, nullptr);
        pthread_cond_init(&serverStartedCond, nullptr);

        Data data{
                .numberOfPlayers = -1,
                .serverAddress = std::string(argv[2]),
                .mutex = &mutex,
                .serverStarted = true,
                .serverStartedCond = &serverStartedCond
        };

        pthread_create(&client, nullptr, &clientThread, &data);

        pthread_join(client, nullptr);

        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&serverStartedCond);
    }

    return 0;
}
