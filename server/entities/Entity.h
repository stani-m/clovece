//
// Created by stanislavmotesicky on 01/12/2021.
//

#ifndef CLOVECE_ENTITY_H
#define CLOVECE_ENTITY_H


#include "../../common/SColor.h"

class Entity {
public:
    void move(const std::pair<int, int> &coord);

    void rotate(float angle);

    void render(int playerSockFd) const;

    std::pair<int, int> getCoordinates() const;

protected:
    Entity(std::pair<int, int> coordinates, float angle, const std::string &assetPath);

private:
    std::pair<int, int> coordinates;
    float angle;

    int textureIndex;
};


#endif //CLOVECE_ENTITY_H
