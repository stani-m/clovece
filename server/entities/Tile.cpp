//
// Created by stanislavmotesicky on 02/12/2021.
//

#include "Tile.h"

Tile::Tile(std::pair<int, int> coordinates, SColor color) :
        Entity(coordinates, 0.0, "textures/" + colorString(color) + "Tile.bmp") {}
