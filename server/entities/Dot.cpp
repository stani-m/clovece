//
// Created by stanislavmotesicky on 03/01/2022.
//

#include "Dot.h"

Dot::Dot(std::pair<int, int> coordinates, SColor color) :
        Entity(coordinates, 0.0, "textures/" + colorString(color) + "Dot.bmp") {}
