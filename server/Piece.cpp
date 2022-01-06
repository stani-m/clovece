//
// Created by stanislavmotesicky on 02/12/2021.
//

#include "Piece.h"

Piece::Piece(int x, int y, Color color) :
        Entity(x, y, 0.0, "textures/" + colorString(color) + "Piece.bmp"), state(PieceState::InStart),
        color(color),
        homeCoordinates(x, y) {}

PieceState Piece::getState() const {
    return state;
}

void Piece::setState(PieceState state) {
    Piece::state = state;
}

Color Piece::getColor() const {
    return color;
}

const std::pair<int, int> &Piece::getHomeCoordinates() const {
    return homeCoordinates;
}