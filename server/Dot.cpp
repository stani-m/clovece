//
// Created by stanislavmotesicky on 03/01/2022.
//

#include "Dot.h"

Dot::Dot(int x, int y, Color color) :
        Entity(x, y, 0.0, "textures/" + colorString(color) + "Dot.bmp") {}
