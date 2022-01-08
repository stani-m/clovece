//
// Created by stanislavmotesicky on 02/12/2021.
//

#include "Tile.h"

Tile::Tile(int x, int y, SColor color) :
        Entity(x, y, 0.0, "textures/" + colorString(color) + "Tile.bmp") {}
