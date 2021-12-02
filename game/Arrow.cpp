//
// Created by stanislavmotesicky on 02/12/2021.
//

#include "Arrow.h"
#include "Direction.h"

Arrow::Arrow(int x, int y, Direction direction, Color color, SDL_Renderer *renderer) :
        Entity(x, y, (float) direction, "assets/" + colorString(color) + "Arrow.bmp", renderer) {}
