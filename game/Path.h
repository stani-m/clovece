//
// Created by stanislavmotesicky on 03/01/2022.
//

#ifndef CLOVECE_PATH_H
#define CLOVECE_PATH_H


#include <vector>
#include "Entity.h"

class Path {
public:
    Path(SDL_Renderer *renderer);

    void render(SDL_Renderer *renderer) const;
private:
    std::vector<Entity> entities;
};


#endif //CLOVECE_PATH_H
