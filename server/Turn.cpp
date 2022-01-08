//
// Created by stanislavmotesicky on 04/01/2022.
//

#include "Turn.h"
#include <unistd.h>

Turn::Turn(Player &player) : state(TurnState::Started), player(&player), numberOfDiceRolls(0) {

}

bool Turn::advanceTurn() {
    std::pair<int, int> mouseClick = {-1, -1};
    switch (state) {
        case TurnState::Started: {
            if (numberOfDiceRolls == 3) {
                return true;
            }
            player->startTurn();
            state = TurnState::WaitingForRoll;
            return false;
        }
        case TurnState::WaitingForRoll: {
            if (mouseClick == player->diceCoordinates()) {
                player->rollDice();
                numberOfDiceRolls++;
                if (player->getActionsCount() == 0) {
                    state = TurnState::NoActions;
                } else {
                    state = TurnState::WaitingToSelectAction;
                }
            }
            return false;
        }
        case TurnState::WaitingToSelectAction: {
            if (player->doAction(mouseClick)) {
                player->endTurn();
                state = TurnState::WaitingForRoll;
                return true;
            }
            return false;
        }
        case TurnState::NoActions: {
            sleep(1);
            player->endTurn();
            state = TurnState::Started;
            return false;
        }
    }
    return false;
}

Turn &Turn::operator=(Turn &&other) noexcept {
    state = other.state;
    player = other.player;
    numberOfDiceRolls = other.numberOfDiceRolls;
    return *this;
}

Player *Turn::getPlayer() const {
    return player;
}
