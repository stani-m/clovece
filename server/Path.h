//
// Created by stanislavmotesicky on 03/01/2022.
//

#ifndef CLOVECE_PATH_H
#define CLOVECE_PATH_H


#include <vector>
#include <array>
#include "entities/Entity.h"
#include "entities/Piece.h"

class Path {
public:
    explicit Path();

    void render(int playerSockFd) const;

    std::pair<std::pair<int, int>, PieceState> getNextCoordinates(const Piece &piece, int moveLength) const;

private:
    std::array<std::pair<int, int>, 44> redPath;
    std::array<std::pair<int, int>, 44> bluePath;
    std::array<std::pair<int, int>, 44> greenPath;
    std::array<std::pair<int, int>, 44> yellowPath;

    std::vector<Entity> entities;
};


#endif //CLOVECE_PATH_H
