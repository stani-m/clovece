//
// Created by stanislavmotesicky on 03/01/2022.
//

#include "Path.h"
#include "Tile.h"
#include "Piece.h"
#include "Direction.h"
#include "Arrow.h"

Path::Path(SDL_Renderer *renderer) {

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
}

void Path::render(SDL_Renderer *renderer) const {
    for (const auto &entity: entities) {
        entity.render(renderer);
    }
}
