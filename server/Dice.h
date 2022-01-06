//
// Created by stanislavmotesicky on 03/01/2022.
//

#ifndef CLOVECE_DICE_H
#define CLOVECE_DICE_H


#include "Entity.h"

class Dice : public Entity  {
public:
    Dice(int x, int y, int number);

    int getNumber() const;

private:
    int number;
};


#endif //CLOVECE_DICE_H
