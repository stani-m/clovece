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
#include "Dice.h"
#include "Path.h"

class Player {
public:
    Player(Color color, const Path *path, SDL_Renderer *renderer);

    Player(Player &&old) noexcept;

    Player &operator=(Player &&other) noexcept;

    void render(SDL_Renderer *renderer) const;

    void startTurn(SDL_Renderer *renderer);

    void rollDice(SDL_Renderer *renderer);

    void endTurn();

    std::pair<int, int> diceCoordinates() const;

    std::pair<int, int> startCoordinates() const;

    bool doAction(const std::pair<int, int> &clickPoint);

    int getActionsCount() const;

    ~Player();

private:
    Color color;

    Path *path;

    std::vector<Entity> entities;

    std::array<Piece *, 4> pieces;

    std::vector<Action> actions;
};


#endif //CLOVECE_PLAYER_H
