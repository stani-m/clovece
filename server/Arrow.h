//
// Created by stanislavmotesicky on 02/12/2021.
//

#ifndef CLOVECE_ARROW_H
#define CLOVECE_ARROW_H


#include "Entity.h"
#include "Direction.h"

class Arrow : public Entity {
public:
    Arrow(int x, int y, Direction direction, SColor color);
};


#endif //CLOVECE_ARROW_H
