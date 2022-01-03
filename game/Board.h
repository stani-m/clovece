//
// Created by stanislavmotesicky on 03/01/2022.
//

#ifndef CLOVECE_BOARD_H
#define CLOVECE_BOARD_H

#include "Path.h"
#include "Player.h"

class Board {
public:
    Board(SDL_Renderer *renderer);

    void render(SDL_Renderer *renderer);
private:
    Path path;
};


#endif //CLOVECE_BOARD_H
