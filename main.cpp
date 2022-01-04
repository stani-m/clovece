#include <cstdio>
#include <SDL2/SDL.h>
#include "game/Tile.h"
#include "game/Game.h"

const int SCREEN_WIDTH = 704;
const int SCREEN_HEIGHT = 704;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Človeče nehnevaj sa!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return 1;
    }

    srand(time(nullptr));

    Game game(renderer);
    game.createPlayer(Color::Red, renderer);
    game.createPlayer(Color::Blue, renderer);
    game.createPlayer(Color::Green, renderer);
    game.createPlayer(Color::Yellow, renderer);

    game.startGame(renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
