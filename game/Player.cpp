//
// Created by stanislavmotesicky on 03/01/2022.
//

#include "Player.h"
#include "Tile.h"
#include "Piece.h"
#include "Dice.h"

Player::Player(Color color, SDL_Renderer *renderer) : color(color), pieces({nullptr, nullptr, nullptr, nullptr}) {
    switch (color) {
        case Color::Red:
            pieces[0] = new Piece(0, 0, Color::Red, renderer);
            pieces[1] = new Piece(1, 0, Color::Red, renderer);
            pieces[2] = new Piece(1, 1, Color::Red, renderer);
            pieces[3] = new Piece(0, 1, Color::Red, renderer);
            entities.push_back(Tile(0, 0, Color::Red, renderer));
            entities.push_back(Tile(1, 0, Color::Red, renderer));
            entities.push_back(Tile(1, 1, Color::Red, renderer));
            entities.push_back(Tile(0, 1, Color::Red, renderer));
            entities.push_back(Tile(1, 5, Color::Red, renderer));
            entities.push_back(Tile(2, 5, Color::Red, renderer));
            entities.push_back(Tile(3, 5, Color::Red, renderer));
            entities.push_back(Tile(4, 5, Color::Red, renderer));
            break;
        case Color::Blue:
            pieces[0] = new Piece(9, 0, Color::Blue, renderer);
            pieces[1] = new Piece(10, 0, Color::Blue, renderer);
            pieces[2] = new Piece(10, 1, Color::Blue, renderer);
            pieces[3] = new Piece(9, 1, Color::Blue, renderer);
            entities.push_back(Tile(9, 0, Color::Blue, renderer));
            entities.push_back(Tile(10, 0, Color::Blue, renderer));
            entities.push_back(Tile(10, 1, Color::Blue, renderer));
            entities.push_back(Tile(9, 1, Color::Blue, renderer));
            entities.push_back(Tile(5, 1, Color::Blue, renderer));
            entities.push_back(Tile(5, 2, Color::Blue, renderer));
            entities.push_back(Tile(5, 3, Color::Blue, renderer));
            entities.push_back(Tile(5, 4, Color::Blue, renderer));
            break;
        case Color::Green:
            pieces[0] = new Piece(9, 9, Color::Green, renderer);
            pieces[1] = new Piece(10, 9, Color::Green, renderer);
            pieces[2] = new Piece(10, 10, Color::Green, renderer);
            pieces[3] = new Piece(9, 10, Color::Green, renderer);
            entities.push_back(Tile(9, 9, Color::Green, renderer));
            entities.push_back(Tile(10, 9, Color::Green, renderer));
            entities.push_back(Tile(10, 10, Color::Green, renderer));
            entities.push_back(Tile(9, 10, Color::Green, renderer));
            entities.push_back(Tile(6, 5, Color::Green, renderer));
            entities.push_back(Tile(7, 5, Color::Green, renderer));
            entities.push_back(Tile(8, 5, Color::Green, renderer));
            entities.push_back(Tile(9, 5, Color::Green, renderer));
            break;
        case Color::Yellow:
            pieces[0] = new Piece(0, 9, Color::Yellow, renderer);
            pieces[1] = new Piece(1, 9, Color::Yellow, renderer);
            pieces[2] = new Piece(1, 10, Color::Yellow, renderer);
            pieces[3] = new Piece(0, 10, Color::Yellow, renderer);
            entities.push_back(Tile(0, 9, Color::Yellow, renderer));
            entities.push_back(Tile(1, 9, Color::Yellow, renderer));
            entities.push_back(Tile(1, 10, Color::Yellow, renderer));
            entities.push_back(Tile(0, 10, Color::Yellow, renderer));
            entities.push_back(Tile(5, 6, Color::Yellow, renderer));
            entities.push_back(Tile(5, 7, Color::Yellow, renderer));
            entities.push_back(Tile(5, 8, Color::Yellow, renderer));
            entities.push_back(Tile(5, 9, Color::Yellow, renderer));
            break;
    }
}

void Player::render(SDL_Renderer *renderer) const {
    for (const auto &entity: entities) {
        entity.render(renderer);
    }
    for (const auto &piece : pieces) {
        piece->render(renderer);
    }
    for (const auto &action: actions) {
        action.getDot().render(renderer);
    }
}

void Player::startTurn(SDL_Renderer *renderer) {
    std::pair<int, int> coordinates = diceCoordinates();
    entities.push_back(Dice(coordinates.first, coordinates.second, 6, renderer));
}

std::pair<int, int> Player::diceCoordinates() const {
    std::pair<int, int> coordinates;
    switch (color) {
        case Color::Red:
            coordinates = {2, 2};
            break;
        case Color::Blue:
            coordinates = {8, 2};
            break;
        case Color::Green:
            coordinates = {8, 8};
            break;
        case Color::Yellow:
            coordinates = {2, 8};
            break;
    }
    return coordinates;
}

std::pair<int, int> Player::startCoordinates() const {
    std::pair<int, int> coordinates;
    switch (color) {
        case Color::Red:
            coordinates = {0, 4};
            break;
        case Color::Blue:
            coordinates = {6, 0};
            break;
        case Color::Green:
            coordinates = {10, 6};
            break;
        case Color::Yellow:
            coordinates = {4, 10};
            break;
    }
    return coordinates;
}


void Player::rollDice(SDL_Renderer *renderer) {
    entities.pop_back();
    Dice dice(5, 5, 6, renderer);
    entities.push_back(dice);
    std::pair<int, int> start = startCoordinates();
    Piece *piece = nullptr;
    for (const auto &item : pieces) {
        if (item->getState() == PieceState::InStart) {
            piece = item;
            break;
        }
    }
    if (piece != nullptr && dice.getNumber() == 6) {
        actions.emplace_back(Action(*piece, start, start, renderer));
    }
}

Player::~Player() {
    for (auto &piece : pieces) {
        delete piece;
    }
}

Player::Player(Player &&old) noexcept: color(old.color), entities(std::move(old.entities)),
                                       pieces(old.pieces), actions(std::move(old.actions)) {
    old.pieces = {nullptr, nullptr, nullptr, nullptr};
}

bool Player::doAction(const std::pair<int, int> &clickPoint) {
    for (auto &action : actions) {
        if (action.getClickPoint() == clickPoint) {
            action.execute();
            return true;
        }
    }
    return false;
}

void Player::endTurn() {
    entities.pop_back();
    actions.clear();
}
