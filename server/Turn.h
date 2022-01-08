//
// Created by stanislavmotesicky on 04/01/2022.
//

#ifndef CLOVECE_TURN_H
#define CLOVECE_TURN_H


#include <tuple>
#include "Player.h"
#include "TurnState.h"

class Turn {
public:
    explicit Turn(Player &player);

    std::pair<std::tuple<bool, bool, int>, bool> advanceTurn();

    Player *getPlayer() const;

    Turn &operator=(Turn &&other) noexcept;

private:
    TurnState state;

    int numberOfDiceRolls;

    Player *player;
};


#endif //CLOVECE_TURN_H
