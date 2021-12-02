//
// Created by stanislavmotesicky on 02/12/2021.
//

#ifndef CLOVECE_TILE_H
#define CLOVECE_TILE_H


#include "Entity.h"

class Tile : public Entity {
public:
    Tile(int x, int y, Color color, SDL_Renderer *renderer);
};


#endif //CLOVECE_TILE_H
