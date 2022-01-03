//
// Created by stanislavmotesicky on 03/01/2022.
//

#ifndef CLOVECE_PLAYER_H
#define CLOVECE_PLAYER_H


#include <vector>
#include <array>
#include "Entity.h"
#include "Dot.h"
#include "Piece.h"
#include "Action.h"

class Player {
public:
    Player(Color color, SDL_Renderer *renderer);

    Player(Player &&old) noexcept;

    void render(SDL_Renderer *renderer) const;

    void startTurn(SDL_Renderer *renderer);

    void rollDice(SDL_Renderer *renderer);

    void endTurn();

    std::pair<int, int> diceCoordinates() const;

    std::pair<int, int> startCoordinates() const;

    bool doAction(const std::pair<int, int> &clickPoint);

    ~Player();

private:
    Color color;

    std::vector<Entity> entities;

    std::array<Piece *, 4> pieces;

    std::vector<Action> actions;
};


#endif //CLOVECE_PLAYER_H
