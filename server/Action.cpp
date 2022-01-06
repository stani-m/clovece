//
// Created by stanislavmotesicky on 03/01/2022.
//

#include "Action.h"

#include <utility>

Action::Action(Piece &piece, const std::pair<int, int> &clickPoint, std::pair<int, int> movePoint, PieceState newState,
               Piece *throwOutPiece)
        : dot(Dot(clickPoint.first, clickPoint.second, piece.getColor())), movePiece(piece),
          movePoint(std::move(movePoint)), newState(newState), throwOutPiece(throwOutPiece) {}

std::pair<int, int> Action::getClickPoint() const {
    return dot.getCoordinates();
}

void Action::execute() {
    if (throwOutPiece != nullptr) {
        throwOutPiece->move(throwOutPiece->getHomeCoordinates());
        throwOutPiece->setState(PieceState::InStart);
    }
    movePiece.move(movePoint);
    movePiece.setState(newState);
}

const Dot &Action::getDot() const {
    return dot;
}
