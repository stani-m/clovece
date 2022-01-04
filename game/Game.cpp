//
// Created by stanislavmotesicky on 03/01/2022.
//

#include "Game.h"
#include "TurnState.h"
#include "Turn.h"

Game::Game(SDL_Renderer *renderer) : board(renderer), playerTurn() {

}

void Game::createPlayer(Color color, SDL_Renderer *renderer) {
    players.emplace_back(std::move(Player(color, board.getPath(), renderer)));
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

    Turn turn(players[playerTurn]);

    while (SDL_WaitEvent(&e)) {
        if (e.type == SDL_QUIT) {
            break;
        }
        std::pair<int, int> mouseClick = {-1, -1};
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            auto *mouseButtonEvent = (SDL_MouseButtonEvent *) &e;
            int x = mouseButtonEvent->x / 64;
            int y = mouseButtonEvent->y / 64;
            mouseClick = {x, y};
        }
        if (turn.advanceTurn(mouseClick, renderer)) {
            playerTurn = (playerTurn + 1) % 4;
            turn = Turn(players[playerTurn]);
        }
        SDL_RenderClear(renderer);
        render(renderer);
        SDL_RenderPresent(renderer);
    }

}
