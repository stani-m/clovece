#include <cstdio>
#include <SDL2/SDL.h>
#include "server/Game.h"
#include "client/Client.h"
#include <pthread.h>

const int SCREEN_WIDTH = 704;
const int SCREEN_HEIGHT = 704;

const int PORT = 1234;

typedef struct Data {
    SDL_Renderer *renderer;
    int numberOfPlayers;
    std::string serverAddress;
    pthread_mutex_t *mutex;
    bool serverStarted;
    pthread_cond_t *serverStartedCond;
} Data;

void *serverThread(void *arg) {
    auto *data = static_cast<Data *>(arg);

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

    Client client(data->renderer);

    pthread_mutex_lock(data->mutex);
    while (!data->serverStarted) {
        pthread_cond_wait(data->serverStartedCond, data->mutex);
    }
    client.start(data->serverAddress, PORT);
    pthread_mutex_unlock(data->mutex);

    return nullptr;
}

std::pair<SDL_Window *, SDL_Renderer *> createRenderer() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return {nullptr, nullptr};
    }

    SDL_Window *window = SDL_CreateWindow("Človeče nehnevaj sa!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return {nullptr, nullptr};
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);

        return {nullptr, nullptr};
    }
    return {window, renderer};
}

int main(int argn, char *argv[]) {
    if (argn < 3) {
        fprintf(stderr, "incorrect number of arguments\n");
        return 1;
    }

    if (std::string(argv[1]) == "start") {
        auto[window, renderer] = createRenderer();
        if (renderer == nullptr) {
            return 1;
        }

        srand(time(nullptr));

        pthread_t server, client;

        pthread_mutex_t mutex;
        pthread_cond_t serverStartedCond;

        pthread_mutex_init(&mutex, nullptr);
        pthread_cond_init(&serverStartedCond, nullptr);

        Data data{
                .renderer = renderer,
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

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        SDL_Quit();
    } else if (std::string(argv[1]) == "connect") {
        auto[window, renderer] = createRenderer();
        if (renderer == nullptr) {
            return 1;
        }

        srand(time(nullptr));

        pthread_t client;

        pthread_mutex_t mutex;
        pthread_cond_t serverStartedCond;

        pthread_mutex_init(&mutex, nullptr);
        pthread_cond_init(&serverStartedCond, nullptr);

        Data data{
                .renderer = renderer,
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

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        SDL_Quit();
    }
    return 0;
}
