//
// Created by stanislavmotesicky on 02/12/2021.
//

#include "Arrow.h"

Arrow::Arrow(int x, int y, Direction direction, SColor color) :
        Entity(x, (float) direction, "textures/" + colorString(color) + "Arrow.bmp") {}
