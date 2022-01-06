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

    void render(SDL_Renderer *renderer);

    void startListening();

    virtual ~Game();

private:
    void createPlayer(Color color);

    int port;

    int sockfd;
    struct sockaddr_in serv_addr;

    Board board;

    std::vector<Player> players;

    int playerTurn;
};


#endif //CLOVECE_GAME_H
