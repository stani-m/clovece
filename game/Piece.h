//
// Created by stanislavmotesicky on 02/12/2021.
//

#ifndef CLOVECE_PIECE_H
#define CLOVECE_PIECE_H


#include "Entity.h"
#include "PieceState.h"

class Piece : public Entity {
public:
    Piece(int x, int y, Color color, SDL_Renderer *renderer);

    PieceState getState() const;

    void setState(PieceState state);

    Color getColor() const;

    const std::pair<int, int> &getHomeCoordinates() const;

private:
    PieceState state;

    std::pair<int, int> homeCoordinates;

    Color color;
};


#endif //CLOVECE_PIECE_H
