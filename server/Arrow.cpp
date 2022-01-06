//
// Created by stanislavmotesicky on 02/12/2021.
//

#include "Arrow.h"
#include "Direction.h"

Arrow::Arrow(int x, int y, Direction direction, Color color) :
        Entity(x, y, (float) direction, "textures/" + colorString(color) + "Arrow.bmp") {}
