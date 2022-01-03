//
// Created by stanislavmotesicky on 03/01/2022.
//

#include "Board.h"

Board::Board(SDL_Renderer *renderer): path(renderer) {

}

void Board::render(SDL_Renderer *renderer) {
    path.render(renderer);
}
