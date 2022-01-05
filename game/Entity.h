//
// Created by stanislavmotesicky on 01/12/2021.
//

#ifndef CLOVECE_ENTITY_H
#define CLOVECE_ENTITY_H


#include <SDL2/SDL.h>
#include "Color.h"

class Entity {
public:
    void move(const std::pair<int, int> &coordinates);

    void rotate(float angle);

    void render(SDL_Renderer *renderer) const;

    std::pair<int, int> getCoordinates() const;

    ~Entity();

protected:
    Entity(int x, int y, float angle, const std::string &assetPath, SDL_Renderer *renderer);

private:
    int x;
    int y;
    float angle;

    SDL_Texture *texture;
    SDL_Rect rectangle{};
};


#endif //CLOVECE_ENTITY_H
