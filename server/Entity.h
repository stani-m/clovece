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

    void render() const;

    [[nodiscard]] std::pair<int, int> getCoordinates() const;

protected:
    Entity(int x, int y, float angle, const std::string &assetPath);

private:
    int x;
    int y;
    float angle;

    int textureIndex;
    SDL_Rect rectangle{};
};


#endif //CLOVECE_ENTITY_H
