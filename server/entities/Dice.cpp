//
// Created by stanislavmotesicky on 03/01/2022.
//

#include "Dice.h"

Dice::Dice(std::pair<int, int> coordinates, int number) :
        Entity(coordinates, 0.0, "textures/Dice" + std::to_string(number) + ".bmp"), number(number) {}

int Dice::getNumber() const {
    return number;
}
