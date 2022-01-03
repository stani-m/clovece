//
// Created by stanislavmotesicky on 03/01/2022.
//

#include "Dot.h"

Dot::Dot(int x, int y, Color color, SDL_Renderer *renderer) :
        Entity(x, y, 0.0, "assets/" + colorString(color) + "Dot.bmp", renderer) {}
