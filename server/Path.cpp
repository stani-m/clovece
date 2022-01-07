//
// Created by stanislavmotesicky on 03/01/2022.
//

#include "Path.h"
#include "Tile.h"
#include "Piece.h"
#include "Direction.h"
#include "Arrow.h"

// 0 - 39
// 10 - 9
// 20 - 19
// 30 - 29

Path::Path() {

    int generalPath[40][2] = {
            {0,  4},
            {1,  4},
            {2,  4},
            {3,  4},
            {4,  4},
            {4,  3},
            {4,  2},
            {4,  1},
            {4,  0},
            {5,  0},
            {6,  0},
            {6,  1},
            {6,  2},
            {6,  3},
            {6,  4},
            {7,  4},
            {8,  4},
            {9,  4},
            {10, 4},
            {10, 5},
            {10, 6},
            {9,  6},
            {8,  6},
            {7,  6},
            {6,  6},
            {6,  7},
            {6,  8},
            {6,  9},
            {6,  10},
            {5,  10},
            {4,  10},
            {4,  9},
            {4,  8},
            {4,  7},
            {4,  6},
            {3,  6},
            {2,  6},
            {1,  6},
            {0,  6},
            {0,  5}
    };
    for (int i = 0; i < 40; ++i) {
        redPath[i] = {generalPath[i][0], generalPath[i][1]};
        bluePath[i] = {generalPath[(i + 10) % 40][0], generalPath[(i + 10) % 40][1]};
        greenPath[i] = {generalPath[(i + 20) % 40][0], generalPath[(i + 20) % 40][1]};
        yellowPath[i] = {generalPath[(i + 30) % 40][0], generalPath[(i + 30) % 40][1]};
        entities.push_back(Tile(generalPath[i][0], generalPath[i][1], Color::White));
    }

    int redEndCoords[4][2] = {
            {1, 5},
            {2, 5},
            {3, 5},
            {4, 5}
    };
    int blueEndCoords[4][2] = {
            {5, 1},
            {5, 2},
            {5, 3},
            {5, 4}
    };
    int greenEndCoords[4][2] = {
            {9, 5},
            {8, 5},
            {7, 5},
            {6, 5}
    };
    int yellowEndCoords[4][2] = {
            {5, 9},
            {5, 8},
            {5, 7},
            {5, 6}
    };
    for (int i = 0; i < 4; ++i) {
        redPath[40 + i] = {redEndCoords[i][0], redEndCoords[i][1]};
        bluePath[40 + i] = {blueEndCoords[i][0], blueEndCoords[i][1]};
        greenPath[40 + i] = {greenEndCoords[i][0], greenEndCoords[i][1]};
        yellowPath[40 + i] = {yellowEndCoords[i][0], yellowEndCoords[i][1]};
        entities.push_back(Tile(redEndCoords[i][0], redEndCoords[i][1], Color::Red));
        entities.push_back(Tile(blueEndCoords[i][0], blueEndCoords[i][1], Color::Blue));
        entities.push_back(Tile(greenEndCoords[i][0], greenEndCoords[i][1], Color::Green));
        entities.push_back(Tile(yellowEndCoords[i][0], yellowEndCoords[i][1], Color::Yellow));
    }

    entities.push_back(Arrow(4, 10, Direction::Up, Color::White));
    entities.push_back(Arrow(10, 6, Direction::Left, Color::White));
    entities.push_back(Arrow(6, 0, Direction::Down, Color::White));
    entities.push_back(Arrow(0, 4, Direction::Right, Color::White));
}

void Path::render(int playerSockFd) const {
    for (const auto &entity: entities) {
        entity.render(playerSockFd);
    }
}

std::pair<std::pair<int, int>, PieceState> Path::getNextCoordinates(const Piece &piece, int moveLength) const {
    std::pair<int, int> pieceCoords = piece.getCoordinates();
    const std::array<std::pair<int, int>, 44> *path = nullptr;
    switch (piece.getColor()) {
        case Color::Red:
            path = &redPath;
            break;
        case Color::Blue:
            path = &bluePath;
            break;
        case Color::Green:
            path = &greenPath;
            break;
        case Color::Yellow:
            path = &yellowPath;
            break;
    }
    int currentIndex = -1;
    for (int i = 0; i < 44; ++i) {
        if ((*path)[i] == pieceCoords) {
            currentIndex = i;
        }
    }
    if (currentIndex == -1) {
        return {{-1, -1}, PieceState::Invalid};
    }
    int nextIndex = currentIndex + moveLength;
    if (nextIndex < 44) {
        if (nextIndex >= 40) {
            return {(*path)[nextIndex], PieceState::InEnd};
        } else {
            return {(*path)[nextIndex], PieceState::OnPath};
        }
    }
    return {{-1, -1}, PieceState::Invalid};
}
