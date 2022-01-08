//
// Created by stanislavmotesicky on 03/01/2022.
//

#ifndef CLOVECE_PLAYER_H
#define CLOVECE_PLAYER_H

class Board;

#include <vector>
#include <array>
#include <netinet/in.h>
#include "Entity.h"
#include "Piece.h"
#include "Action.h"
#include "Board.h"

class Player {
public:
    Player(SColor color, Board &board, int sockFd);

    Player(Player &&old) noexcept;

    Player &operator=(Player &&other) noexcept;

    void startRender() const;

    void render(int targetPlayerSockFd) const;

    void renderActions(int targetPlayerSockFd) const;

    void presentRender() const;

    void startTurn();

    void rollDice();

    void endTurn();

    std::pair<int, int> diceCoordinates() const;

    std::pair<int, int> startCoordinates() const;

    bool doAction(const std::pair<int, int> &clickPoint);

    int getActionsCount() const;

    const std::array<Piece *, 4> &getPieces() const;

    SColor getSColor() const;

    int getPlayerSockFd() const;

    void quit() const;

    ~Player();

private:
    SColor color;

    int playerSockFd;
    struct sockaddr_in cliAddr;

    Board &board;

    std::vector<Entity> entities;

    std::array<Piece *, 4> pieces;

    std::vector<Action> actions;
};


#endif //CLOVECE_PLAYER_H
