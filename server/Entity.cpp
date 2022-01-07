//
// Created by stanislavmotesicky on 01/12/2021.
//

#include <stdexcept>
#include "Entity.h"

Entity::Entity(int x, int y, float angle, const std::string &assetPath) :
        x(x), y(y), angle(angle) {

    if (assetPath == "textures/RedPiece.bmp")
        textureIndex = 0;
    else if (assetPath == "textures/BluePiece.bmp")
        textureIndex = 1;
    else if (assetPath == "textures/GreenPiece.bmp")
        textureIndex = 2;
    else if (assetPath == "textures/YellowPiece.bmp")
        textureIndex = 3;
    else if (assetPath == "textures/RedTile.bmp")
        textureIndex = 4;
    else if (assetPath == "textures/BlueTile.bmp")
        textureIndex = 5;
    else if (assetPath == "textures/GreenTile.bmp")
        textureIndex = 6;
    else if (assetPath == "textures/YellowTile.bmp")
        textureIndex = 7;
    else if (assetPath == "textures/WhiteTile.bmp")
        textureIndex = 8;
    else if (assetPath == "textures/RedDot.bmp")
        textureIndex = 9;
    else if (assetPath == "textures/BlueDot.bmp")
        textureIndex = 10;
    else if (assetPath == "textures/GreenDot.bmp")
        textureIndex = 11;
    else if (assetPath == "textures/YellowDot.bmp")
        textureIndex = 12;
    else if (assetPath == "textures/WhiteArrow.bmp")
        textureIndex = 13;
    else if (assetPath == "textures/Dice1.bmp")
        textureIndex = 14;
    else if (assetPath == "textures/Dice2.bmp")
        textureIndex = 15;
    else if (assetPath == "textures/Dice3.bmp")
        textureIndex = 16;
    else if (assetPath == "textures/Dice4.bmp")
        textureIndex = 17;
    else if (assetPath == "textures/Dice5.bmp")
        textureIndex = 18;
    else if (assetPath == "textures/Dice6.bmp")
        textureIndex = 19;
}

void Entity::move(const std::pair<int, int> &coordinates) {
    this->x = coordinates.first;
    this->y = coordinates.second;
}

void Entity::render() const {
}

void Entity::rotate(float newAngle) {
    angle = newAngle;
}

std::pair<int, int> Entity::getCoordinates() const {
    return {x, y};
}
