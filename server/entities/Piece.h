//
// Created by stanislavmotesicky on 02/12/2021.
//

#ifndef CLOVECE_PIECE_H
#define CLOVECE_PIECE_H


#include "Entity.h"
#include "PieceState.h"

class Piece : public Entity {
public:
    Piece(std::pair<int, int> coordinates, SColor color);

    PieceState getState() const;

    void setState(PieceState pieceState);

    SColor getSColor() const;

    const std::pair<int, int> &getHomeCoordinates() const;

private:
    PieceState state;

    std::pair<int, int> homeCoordinates;

    SColor color;
};


#endif //CLOVECE_PIECE_H
