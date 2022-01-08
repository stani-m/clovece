//
// Created by stanislavmotesicky on 02/12/2021.
//

#include "Piece.h"

Piece::Piece(std::pair<int, int> coordinates, SColor color) :
        Entity(coordinates, 0.0, "textures/" + colorString(color) + "Piece.bmp"), state(PieceState::InStart),
        color(color),
        homeCoordinates(coordinates) {}

PieceState Piece::getState() const {
    return state;
}

void Piece::setState(PieceState pieceState) {
    state = pieceState;
}

SColor Piece::getSColor() const {
    return color;
}

const std::pair<int, int> &Piece::getHomeCoordinates() const {
    return homeCoordinates;
}
