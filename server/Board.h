//
// Created by stanislavmotesicky on 03/01/2022.
//

#ifndef CLOVECE_BOARD_H
#define CLOVECE_BOARD_H

class Player;

#include "Path.h"
#include "Player.h"

class Board {
public:
    explicit Board(std::vector<Player> *players);

    void render(int playerSockFd);

    Piece *findPiece(std::pair<int, int> coordinates) const;

    const Path *getPath() const;

private:
    Path path;

    std::vector<Player> *players;
};


#endif //CLOVECE_BOARD_H
