//
// Created by stanislavmotesicky on 02/12/2021.
//

#ifndef CLOVECE_PIECE_H
#define CLOVECE_PIECE_H


#include "Entity.h"

class Piece : public Entity {
public:
    Piece(int x, int y, Color color, SDL_Renderer *renderer);
};


#endif //CLOVECE_PIECE_H
