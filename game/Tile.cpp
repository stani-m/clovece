//
// Created by stanislavmotesicky on 02/12/2021.
//

#include "Tile.h"

Tile::Tile(int x, int y, Color color, SDL_Renderer *renderer) :
        Entity(x, y, 0.0, "assets/" + colorString(color) + "Tile.bmp", renderer) {}
