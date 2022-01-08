//
// Created by stanislavmotesicky on 03/01/2022.
//

#ifndef CLOVECE_DOT_H
#define CLOVECE_DOT_H


#include "Entity.h"

class Dot : public Entity {
public:
    Dot(std::pair<int, int> coordinates, SColor color);
};


#endif //CLOVECE_DOT_H
