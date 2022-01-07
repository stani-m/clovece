//
// Created by stanislavmotesicky on 03/01/2022.
//

#include <SDL2/SDL.h>
#include <stdexcept>
#include <unistd.h>
#include "Game.h"
#include "Turn.h"
#include "Player.h"

Game::Game(int port) : board(&players), playerTurn() {
    bzero((char *) &servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(port);

    serverSockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSockFd < 0) {
        throw std::runtime_error("Error creating socket");
    }

    int yes = 1;

    setsockopt(serverSockFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    if (bind(serverSockFd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
        throw std::runtime_error("Error binding socket address");
    }
}

void Game::createPlayer(Color color) {
    players.emplace_back(std::move(Player(color, board, serverSockFd)));
}

void Game::render(int playerSockFd) {
    board.render(playerSockFd);
    for (const auto &player: players) {
        player.renderActions(playerSockFd);
    }
    for (const auto &player: players) {
        player.render(playerSockFd);
    }
}

void Game::startGame(int numberOfPlayers) {
    Color colors[4] = {Color::Red, Color::Blue, Color::Green, Color::Yellow};

    for (int i = 0; i < numberOfPlayers; ++i) {
        createPlayer(colors[i]);
    }

    return;

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
        if (turn.advanceTurn(mouseClick)) {
            playerTurn = (playerTurn + 1) % players.size();
            bool allInEnd = true;
            for (const auto &piece: turn.getPlayer()->getPieces()) {
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
    }
}

Game::~Game() {
    close(serverSockFd);
}

void Game::startListening() {
    listen(serverSockFd, 5);
}
