//
// Created by stanislavmotesicky on 04/01/2022.
//

#include "Turn.h"

Turn::Turn(Player &player) : state(TurnState::Started), player(&player), numberOfDiceRolls(0) {

}

bool Turn::advanceTurn(const std::pair<int, int> &mouseClick) {
    SDL_UserEvent dummyEvent = SDL_UserEvent{
            SDL_USEREVENT,
            0,
            0,
            0,
            nullptr,
            nullptr,
    };
    switch (state) {
        case TurnState::Started: {
            if (numberOfDiceRolls == 3) {
                SDL_PushEvent((SDL_Event *) &dummyEvent);
                return true;
            }
            player->startTurn();
            state = TurnState::WaitingForRoll;
            return false;
        }
        case TurnState::WaitingForRoll: {
            std::pair<int, int> coordinates = player->diceCoordinates();
            int diceX = coordinates.first;
            int diceY = coordinates.second;
            if (mouseClick.first == diceX && mouseClick.second == diceY) {
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
            SDL_Delay(1000);
            player->endTurn();
            state = TurnState::Started;
            SDL_PushEvent((SDL_Event *) &dummyEvent);
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
