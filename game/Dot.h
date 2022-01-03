//
// Created by stanislavmotesicky on 03/01/2022.
//

#ifndef CLOVECE_DOT_H
#define CLOVECE_DOT_H


#include "Entity.h"

class Dot : public Entity {
public:
    Dot(int x, int y, Color color, SDL_Renderer *renderer);
};


#endif //CLOVECE_DOT_H
