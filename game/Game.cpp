//
// Created by stanislavmotesicky on 03/01/2022.
//

#include "Game.h"
#include "TurnState.h"

Game::Game(SDL_Renderer *renderer) : board(renderer), playerTurn() {

}

void Game::createPlayer(Color color, SDL_Renderer *renderer) {
    players.emplace_back(std::move(Player(color, renderer)));
}

void Game::render(SDL_Renderer *renderer) {
    board.render(renderer);
    for (const auto &player: players) {
        player.render(renderer);
    }
}

void Game::startGame(SDL_Renderer *renderer) {
    SDL_Event e;

    playerTurn = 0;

    TurnState turnState = TurnState::WaitingForRoll;
    players[playerTurn].startTurn(renderer);

    while (SDL_WaitEvent(&e)) {
        if (e.type == SDL_QUIT) {
            break;
        }
        Player &activePlayer = players[playerTurn];
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            auto *mouseButtonEvent = (SDL_MouseButtonEvent *) &e;
            int x = mouseButtonEvent->x / 64;
            int y = mouseButtonEvent->y / 64;
            switch (turnState) {
                case TurnState::WaitingForRoll: {
                    std::pair<int, int> coordinates = activePlayer.diceCoordinates();
                    int diceX = coordinates.first;
                    int diceY = coordinates.second;
                    if (x == diceX && y == diceY) {
                        turnState = TurnState::WaitingToSelectAction;
                        activePlayer.rollDice(renderer);
                    }
                    break;
                }
                case TurnState::WaitingToSelectAction:
                    if (activePlayer.doAction({x, y})) {
                        activePlayer.endTurn();
                        playerTurn = (playerTurn + 1) % 4;
                        Player &nextPlayer = players[playerTurn];
                        turnState = TurnState::WaitingForRoll;
                        nextPlayer.startTurn(renderer);
                    }
                    break;
            }
        }
        SDL_RenderClear(renderer);
        render(renderer);
        SDL_RenderPresent(renderer);
    }

}
