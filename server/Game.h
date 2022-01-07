//
// Created by stanislavmotesicky on 03/01/2022.
//

#ifndef CLOVECE_GAME_H
#define CLOVECE_GAME_H

#include <sys/socket.h>
#include <netinet/in.h>

#include "Board.h"

class Game {
public:
    Game(int port);

    void startGame(int numberOfPlayers);

    void render(int playerSockFd);

    void startListening();

    virtual ~Game();

private:
    void createPlayer(Color color);

    int serverSockFd;
    struct sockaddr_in servAddr;

    Board board;

    std::vector<Player> players;

    int playerTurn;
};


#endif //CLOVECE_GAME_H
