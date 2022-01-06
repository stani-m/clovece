//
// Created by stanislavmotesicky on 03/01/2022.
//

#include "Dice.h"

Dice::Dice(int x, int y, int number) :
        Entity(x, y, 0.0, "textures/Dice" + std::to_string(number) + ".bmp"), number(number) {}

int Dice::getNumber() const {
    return number;
}
