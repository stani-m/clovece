//
// Created by stanislavmotesicky on 03/01/2022.
//

#ifndef CLOVECE_GAME_H
#define CLOVECE_GAME_H


#include "Board.h"

class Game {
public:
    Game(SDL_Renderer *renderer);

    void createPlayer(Color color, SDL_Renderer *renderer);

    void startGame(SDL_Renderer *renderer);

    void render(SDL_Renderer *renderer);

private:
    Board board;

    std::vector<Player> players;

    int playerTurn;
};


#endif //CLOVECE_GAME_H
