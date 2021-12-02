#include <cstdio>
#include <SDL2/SDL.h>
#include <vector>
#include "game/Piece.h"
#include "game/Tile.h"
#include "game/Arrow.h"
#include "game/Direction.h"

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

    std::vector<Entity> entities;

    entities.push_back(Tile(0, 0, Color::Red, renderer));
    entities.push_back(Piece(0, 0, Color::Red, renderer));
    entities.push_back(Tile(1, 0, Color::Red, renderer));
    entities.push_back(Piece(1, 0, Color::Red, renderer));
    entities.push_back(Tile(1, 1, Color::Red, renderer));
    entities.push_back(Piece(1, 1, Color::Red, renderer));
    entities.push_back(Tile(0, 1, Color::Red, renderer));
    entities.push_back(Piece(0, 1, Color::Red, renderer));
    entities.push_back(Tile(1, 5, Color::Red, renderer));
    entities.push_back(Tile(2, 5, Color::Red, renderer));
    entities.push_back(Tile(3, 5, Color::Red, renderer));
    entities.push_back(Tile(4, 5, Color::Red, renderer));

    entities.push_back(Tile(9, 0, Color::Blue, renderer));
    entities.push_back(Piece(9, 0, Color::Blue, renderer));
    entities.push_back(Tile(10, 0, Color::Blue, renderer));
    entities.push_back(Piece(10, 0, Color::Blue, renderer));
    entities.push_back(Tile(10, 1, Color::Blue, renderer));
    entities.push_back(Piece(10, 1, Color::Blue, renderer));
    entities.push_back(Tile(9, 1, Color::Blue, renderer));
    entities.push_back(Piece(9, 1, Color::Blue, renderer));
    entities.push_back(Tile(5, 1, Color::Blue, renderer));
    entities.push_back(Tile(5, 2, Color::Blue, renderer));
    entities.push_back(Tile(5, 3, Color::Blue, renderer));
    entities.push_back(Tile(5, 4, Color::Blue, renderer));

    entities.push_back(Tile(9, 9, Color::Green, renderer));
    entities.push_back(Piece(9, 9, Color::Green, renderer));
    entities.push_back(Tile(10, 9, Color::Green, renderer));
    entities.push_back(Piece(10, 9, Color::Green, renderer));
    entities.push_back(Tile(10, 10, Color::Green, renderer));
    entities.push_back(Piece(10, 10, Color::Green, renderer));
    entities.push_back(Tile(9, 10, Color::Green, renderer));
    entities.push_back(Piece(9, 10, Color::Green, renderer));
    entities.push_back(Tile(6, 5, Color::Green, renderer));
    entities.push_back(Tile(7, 5, Color::Green, renderer));
    entities.push_back(Tile(8, 5, Color::Green, renderer));
    entities.push_back(Tile(9, 5, Color::Green, renderer));

    entities.push_back(Tile(0, 9, Color::Yellow, renderer));
    entities.push_back(Piece(0, 9, Color::Yellow, renderer));
    entities.push_back(Tile(1, 9, Color::Yellow, renderer));
    entities.push_back(Piece(1, 9, Color::Yellow, renderer));
    entities.push_back(Tile(1, 10, Color::Yellow, renderer));
    entities.push_back(Piece(1, 10, Color::Yellow, renderer));
    entities.push_back(Tile(0, 10, Color::Yellow, renderer));
    entities.push_back(Piece(0, 10, Color::Yellow, renderer));
    entities.push_back(Tile(5, 6, Color::Yellow, renderer));
    entities.push_back(Tile(5, 7, Color::Yellow, renderer));
    entities.push_back(Tile(5, 8, Color::Yellow, renderer));
    entities.push_back(Tile(5, 9, Color::Yellow, renderer));

    entities.push_back(Tile(0, 4, Color::White, renderer));
    entities.push_back(Arrow(0, 4, Direction::Right, Color::White, renderer));
    entities.push_back(Tile(1, 4, Color::White, renderer));
    entities.push_back(Tile(2, 4, Color::White, renderer));
    entities.push_back(Tile(3, 4, Color::White, renderer));
    entities.push_back(Tile(4, 4, Color::White, renderer));
    entities.push_back(Tile(4, 3, Color::White, renderer));
    entities.push_back(Tile(4, 2, Color::White, renderer));
    entities.push_back(Tile(4, 1, Color::White, renderer));
    entities.push_back(Tile(4, 0, Color::White, renderer));
    entities.push_back(Tile(5, 0, Color::White, renderer));
    entities.push_back(Tile(6, 0, Color::White, renderer));
    entities.push_back(Arrow(6, 0, Direction::Down, Color::White, renderer));
    entities.push_back(Tile(6, 1, Color::White, renderer));
    entities.push_back(Tile(6, 2, Color::White, renderer));
    entities.push_back(Tile(6, 3, Color::White, renderer));
    entities.push_back(Tile(6, 4, Color::White, renderer));
    entities.push_back(Tile(7, 4, Color::White, renderer));
    entities.push_back(Tile(8, 4, Color::White, renderer));
    entities.push_back(Tile(9, 4, Color::White, renderer));
    entities.push_back(Tile(10, 4, Color::White, renderer));
    entities.push_back(Tile(10, 5, Color::White, renderer));
    entities.push_back(Tile(10, 6, Color::White, renderer));
    entities.push_back(Arrow(10, 6, Direction::Left, Color::White, renderer));
    entities.push_back(Tile(9, 6, Color::White, renderer));
    entities.push_back(Tile(8, 6, Color::White, renderer));
    entities.push_back(Tile(7, 6, Color::White, renderer));
    entities.push_back(Tile(6, 6, Color::White, renderer));
    entities.push_back(Tile(6, 7, Color::White, renderer));
    entities.push_back(Tile(6, 8, Color::White, renderer));
    entities.push_back(Tile(6, 9, Color::White, renderer));
    entities.push_back(Tile(6, 10, Color::White, renderer));
    entities.push_back(Tile(5, 10, Color::White, renderer));
    entities.push_back(Tile(4, 10, Color::White, renderer));
    entities.push_back(Arrow(4, 10, Direction::Up, Color::White, renderer));
    entities.push_back(Tile(4, 9, Color::White, renderer));
    entities.push_back(Tile(4, 8, Color::White, renderer));
    entities.push_back(Tile(4, 7, Color::White, renderer));
    entities.push_back(Tile(4, 6, Color::White, renderer));
    entities.push_back(Tile(3, 6, Color::White, renderer));
    entities.push_back(Tile(2, 6, Color::White, renderer));
    entities.push_back(Tile(1, 6, Color::White, renderer));
    entities.push_back(Tile(0, 6, Color::White, renderer));
    entities.push_back(Tile(0, 5, Color::White, renderer));

    SDL_RenderClear(renderer);

    for (const auto &entity : entities) {
        entity.render(renderer);
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(10000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
