//
// Created by stanislavmotesicky on 03/01/2022.
//

#include "Dice.h"

Dice::Dice(int x, int y, int number, SDL_Renderer *renderer) :
        Entity(x, y, 0.0, "assets/Dice" + std::to_string(number) + ".bmp", renderer), number(number) {}

int Dice::getNumber() const {
    return number;
}
