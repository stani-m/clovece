//
// Created by stanislavmotesicky on 03/01/2022.
//

#include "Game.h"
#include "Turn.h"
#include "Player.h"

Game::Game(SDL_Renderer *renderer) : board(&players, renderer), playerTurn() {

}

void Game::createPlayer(Color color, SDL_Renderer *renderer) {
    players.emplace_back(std::move(Player(color, board, renderer)));
}

void Game::render(SDL_Renderer *renderer) {
    board.render(renderer);
    for (const auto &player: players) {
        player.renderActions(renderer);
    }
    for (const auto &player: players) {
        player.render(renderer);
    }
}

void Game::startGame(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

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
            bool allInEnd = true;
            for (const auto &piece : turn.getPlayer()->getPieces()) {
                if (piece->getState() != PieceState::InEnd) {
                    allInEnd = false;
                    break;
                }
            }
            if (allInEnd) {
                printf("%s player won!\n", colorString(turn.getPlayer()->getColor()).c_str());
                break;
            }
            turn = Turn(players[playerTurn]);
        }
        SDL_RenderClear(renderer);
        render(renderer);
        SDL_RenderPresent(renderer);
    }
}
