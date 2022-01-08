//
// Created by stanislavmotesicky on 02/12/2021.
//

#ifndef CLOVECE_TILE_H
#define CLOVECE_TILE_H


#include "Entity.h"

class Tile : public Entity {
public:
    Tile(std::pair<int, int> coordinates, SColor color);
};


#endif //CLOVECE_TILE_H
