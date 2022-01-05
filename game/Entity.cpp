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

void Entity::move(const std::pair<int, int> &coordinates) {
    this->x = coordinates.first;
    this->y = coordinates.second;
    rectangle.x = x * 64;
    rectangle.y = y * 64;
}

void Entity::render(SDL_Renderer *renderer) const {
    SDL_RenderCopyEx(renderer, texture, nullptr, &rectangle, angle, nullptr, SDL_FLIP_NONE);
}

Entity::~Entity() {
//    SDL_DestroyTexture(texture); // For some reason this causes an invalid read
}

void Entity::rotate(float newAngle) {
    angle = newAngle;
}

std::pair<int, int> Entity::getCoordinates() const {
    return {x, y};
}
