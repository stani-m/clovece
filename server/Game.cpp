//
// Created by stanislavmotesicky on 03/01/2022.
//

#include <stdexcept>
#include <unistd.h>
#include <cstring>
#include "Game.h"
#include "Turn.h"
#include "../common/messages.h"

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

void Game::createPlayer(SColor color) {
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
    SColor colors[4] = {SColor::Red, SColor::Blue, SColor::Green, SColor::Yellow};

    for (int i = 0; i < numberOfPlayers; ++i) {
        createPlayer(colors[i]);
    }

    playerTurn = 0;

    Turn turn(players[playerTurn]);

    while (true) {
        auto[info, endTurn] = turn.advanceTurn();
        auto[quit, redraw, wait] = info;

        if (quit) {
            for (const auto &player: players) {
                player.sendMessage(PRINT_MESSAGE);
                player.sendMessage("Game has ended due to a player disconnecting.");
                player.quit();
            }
            break;
        }
        if (endTurn) {
            bool allInEnd = true;
            for (const auto &piece: turn.getPlayer()->getPieces()) {
                if (piece->getState() != PieceState::InEnd) {
                    allInEnd = false;
                    break;
                }
            }
            if (allInEnd) {
                for (const auto &player: players) {
                    player.sendMessage(PRINT_MESSAGE);
                    player.sendMessage(colorString(turn.getPlayer()->getSColor()) + " player won!");
                    player.quit();
                }
                break;
            }
            playerTurn = (playerTurn + 1) % (int) players.size();
            turn = Turn(players[playerTurn]);
        }

        if (redraw) {
            for (const auto &player: players) {
                player.startRender();
                render(player.getPlayerSockFd());
                player.presentRender();
            }
        }
        sleep(wait);
    }
}

Game::~Game() {
    close(serverSockFd);
}

void Game::startListening() const {
    listen(serverSockFd, 5);
}
