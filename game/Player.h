//
// Created by stanislavmotesicky on 03/01/2022.
//

#ifndef CLOVECE_PLAYER_H
#define CLOVECE_PLAYER_H

class Board;

#include <vector>
#include <array>
#include "Entity.h"
#include "Piece.h"
#include "Action.h"
#include "Board.h"

class Player {
public:
    Player(Color color, Board &board, SDL_Renderer *renderer);

    Player(Player &&old) noexcept;

    Player &operator=(Player &&other) noexcept;

    void render(SDL_Renderer *renderer) const;

    void renderActions(SDL_Renderer *renderer) const;

    void startTurn(SDL_Renderer *renderer);

    void rollDice(SDL_Renderer *renderer);

    void endTurn();

    std::pair<int, int> diceCoordinates() const;

    std::pair<int, int> startCoordinates() const;

    bool doAction(const std::pair<int, int> &clickPoint);

    int getActionsCount() const;

    const std::array<Piece *, 4> &getPieces() const;

    Color getColor() const;

    ~Player();

private:
    Color color;

    Board &board;

    std::vector<Entity> entities;

    std::array<Piece *, 4> pieces;

    std::vector<Action> actions;
};


#endif //CLOVECE_PLAYER_H
