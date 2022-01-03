//
// Created by stanislavmotesicky on 03/01/2022.
//

#include "Action.h"

Action::Action(Piece &piece, const std::pair<int, int> &clickPoint, const std::pair<int, int> &movePoint,
               SDL_Renderer *renderer)
        : dot(Dot(clickPoint.first, clickPoint.second, piece.getColor(), renderer)), piece(piece),
          movePoint(movePoint) {}

std::pair<int, int> Action::getClickPoint() const {
    return {dot.getX(), dot.getY()};
}

void Action::execute() {
    piece.move(movePoint.first, movePoint.second);
    piece.setState(PieceState::OnPath);
}

const Dot &Action::getDot() const {
    return dot;
}
