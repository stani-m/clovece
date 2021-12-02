//
// Created by stanislavmotesicky on 01/12/2021.
//

#include <stdexcept>
#include "Entity.h"

Entity::Entity(int x, int y, float angle, const std::string &assetPath, SDL_Renderer *renderer) :
        x(x), y(y), angle(angle) {
    SDL_Surface *piece_surface = SDL_LoadBMP(assetPath.c_str());
    if (piece_surface == nullptr) {
        throw std::runtime_error("Loading assets failed!");
    }

    texture = SDL_CreateTextureFromSurface(renderer, piece_surface);
    SDL_FreeSurface(piece_surface);
    if (texture == nullptr) {
        throw std::runtime_error("Something failed!");
    }

    rectangle.x = x * 64;
    rectangle.y = y * 64;
    rectangle.h = 64;
    rectangle.w = 64;
}

void Entity::move(int newX, int newY) {
    this->x = newX;
    this->y = newY;
    rectangle.x = x * 64;
    rectangle.y = y * 64;
}

void Entity::render(SDL_Renderer *renderer) const {
    SDL_RenderCopyEx(renderer, texture, nullptr, &rectangle, angle, nullptr, SDL_FLIP_NONE);
}

Entity::~Entity() {
//    SDL_DestroyTexture(texture); // For some reason this causes an invalid read
}

int Entity::getX() const {
    return x;
}

int Entity::getY() const {
    return y;
}

void Entity::rotate(float newAngle) {
    angle = newAngle;
}
