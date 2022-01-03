//
// Created by stanislavmotesicky on 02/12/2021.
//

#include "Piece.h"

Piece::Piece(int x, int y, Color color, SDL_Renderer *renderer) :
        Entity(x, y, 0.0, "assets/" + colorString(color) + "Piece.bmp", renderer), state(PieceState::InStart), color(color) {}

PieceState Piece::getState() const {
    return state;
}

void Piece::setState(PieceState state) {
    Piece::state = state;
}

Color Piece::getColor() const {
    return color;
}
