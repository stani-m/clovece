//
// Created by stanislavmotesicky on 03/01/2022.
//

#ifndef CLOVECE_ACTION_H
#define CLOVECE_ACTION_H


#include "Dot.h"
#include "Piece.h"

class Action {
public:
    Action(Piece &piece, const std::pair<int, int> &clickPoint, std::pair<int, int> movePoint,
           SDL_Renderer *renderer);

    std::pair<int, int> getClickPoint() const;

    void execute();

    const Dot &getDot() const;

private:
    Dot dot;

    Piece &piece;

    std::pair<int, int> movePoint;
};


#endif //CLOVECE_ACTION_H
