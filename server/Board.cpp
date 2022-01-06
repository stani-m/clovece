//
// Created by stanislavmotesicky on 03/01/2022.
//

#include "Board.h"

Board::Board(std::vector<Player> *players) : players(players) {

}

void Board::render(SDL_Renderer *renderer) {
    path.render(renderer);
}

const Path *Board::getPath() const {
    return &path;
}

Piece *Board::findPiece(std::pair<int, int> coordinates) const {
    for (const auto &player : *players) {
        for (const auto &piece : player.getPieces()) {
            if (piece->getCoordinates() == coordinates) {
                return piece;
            }
        }
    }
    return nullptr;
}
