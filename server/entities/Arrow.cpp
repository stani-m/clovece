//
// Created by stanislavmotesicky on 02/12/2021.
//

#include "Arrow.h"

Arrow::Arrow(std::pair<int, int> coordinates, Direction direction, SColor color) :
        Entity(coordinates, (float) direction, "textures/" + colorString(color) + "Arrow.bmp") {}
