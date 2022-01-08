//
// Created by stanislavmotesicky on 04/01/2022.
//

#include "Turn.h"
#include <unistd.h>
#include <stdexcept>

Turn::Turn(Player &player) : state(TurnState::Started), player(&player), numberOfDiceRolls(0) {

}

std::pair<std::tuple<bool, bool, int>, bool> Turn::advanceTurn() {
    const std::tuple<bool, bool, int> QUIT = {true, false, 0};
    const std::tuple<bool, bool, int> REDRAW = {false, true, 0};

    switch (state) {
        case TurnState::Started: {
            if (numberOfDiceRolls == 3) {
                return {REDRAW, true};
            }
            player->startTurn();
            state = TurnState::WaitingForRoll;
            return {REDRAW, false};
        }
        case TurnState::WaitingForRoll: {
            auto[quit, mouseClick] = player->getClick();
            if (quit) {
                return {QUIT, false};
            } else {
                if (mouseClick == player->diceCoordinates()) {
                    player->rollDice();
                    numberOfDiceRolls++;
                    if (player->getActionsCount() == 0) {
                        state = TurnState::NoActions;
                        return {{false, true, 1}, false};
                    } else {
                        state = TurnState::WaitingToSelectAction;
                        return {REDRAW, false};
                    }
                }
            }
        }
        case TurnState::WaitingToSelectAction: {
            auto[quit, mouseClick] = player->getClick();
            if (quit) {
                return {QUIT, false};
            } else {
                if (player->doAction(mouseClick)) {
                    player->endTurn();
                    return {REDRAW, true};
                }
                return {{false, false, 0}, false};
            }
        }
        case TurnState::NoActions: {
            player->endTurn();
            state = TurnState::Started;
            return {REDRAW, false};
        }
    }
    throw std::runtime_error("Unreachable!");
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
