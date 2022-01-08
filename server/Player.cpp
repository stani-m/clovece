//
// Created by stanislavmotesicky on 03/01/2022.
//

#include <stdexcept>
#include <unistd.h>
#include <cstring>
#include <raylib.h>
#include "Player.h"
#include "entities/Tile.h"
#include "entities/Dice.h"
#include "../common/utils.h"
#include "../common/messages.h"

Player::Player(SColor color, Board &board, int sockFd)
        : color(color), pieces({nullptr, nullptr, nullptr, nullptr}), board(board) {
    switch (color) {
        case SColor::Red:
            pieces[0] = new Piece({0, 0}, SColor::Red);
            pieces[1] = new Piece({1, 0}, SColor::Red);
            pieces[2] = new Piece({1, 1}, SColor::Red);
            pieces[3] = new Piece({0, 1}, SColor::Red);
            entities.push_back(Tile({0, 0}, SColor::Red));
            entities.push_back(Tile({1, 0}, SColor::Red));
            entities.push_back(Tile({1, 1}, SColor::Red));
            entities.push_back(Tile({0, 1}, SColor::Red));
            break;
        case SColor::Blue:
            pieces[0] = new Piece({9, 0}, SColor::Blue);
            pieces[1] = new Piece({10, 0}, SColor::Blue);
            pieces[2] = new Piece({10, 1}, SColor::Blue);
            pieces[3] = new Piece({9, 1}, SColor::Blue);
            entities.push_back(Tile({9, 0}, SColor::Blue));
            entities.push_back(Tile({10, 0}, SColor::Blue));
            entities.push_back(Tile({10, 1}, SColor::Blue));
            entities.push_back(Tile({9, 1}, SColor::Blue));
            break;
        case SColor::Green:
            pieces[0] = new Piece({9, 9}, SColor::Green);
            pieces[1] = new Piece({10, 9}, SColor::Green);
            pieces[2] = new Piece({10, 10}, SColor::Green);
            pieces[3] = new Piece({9, 10}, SColor::Green);
            entities.push_back(Tile({9, 9}, SColor::Green));
            entities.push_back(Tile({10, 9}, SColor::Green));
            entities.push_back(Tile({10, 10}, SColor::Green));
            entities.push_back(Tile({9, 10}, SColor::Green));
            break;
        case SColor::Yellow:
            pieces[0] = new Piece({0, 9}, SColor::Yellow);
            pieces[1] = new Piece({1, 9}, SColor::Yellow);
            pieces[2] = new Piece({1, 10}, SColor::Yellow);
            pieces[3] = new Piece({0, 10}, SColor::Yellow);
            entities.push_back(Tile({0, 9}, SColor::Yellow));
            entities.push_back(Tile({1, 9}, SColor::Yellow));
            entities.push_back(Tile({1, 10}, SColor::Yellow));
            entities.push_back(Tile({0, 10}, SColor::Yellow));
            break;
        default:
            throw std::runtime_error("Unreachable!");
    }

    socklen_t cliLen = sizeof(cliAddr);
    playerSockFd = accept(sockFd, (struct sockaddr *) &cliAddr, &cliLen);
    if (playerSockFd < 0) {
        throw std::runtime_error("ERROR on accept");
    }

    sendInt(playerSockFd, (int) color);
}

void Player::startRender() const {
    sendString(playerSockFd, START_REDRAW);
}

void Player::render(int targetPlayerSockFd) const {
    for (const auto &entity: entities) {
        entity.render(targetPlayerSockFd);
    }
    for (const auto &piece: pieces) {
        piece->render(targetPlayerSockFd);
    }
}

void Player::presentRender() const {
    sendString(playerSockFd, END_REDRAW);
}

void Player::renderActions(int targetPlayerSockFd) const {
    for (const auto &action: actions) {
        action.getDot().render(targetPlayerSockFd);
    }
}

void Player::startTurn() {
    std::pair<int, int> coordinates = diceCoordinates();
    entities.push_back(Dice(coordinates.first, coordinates.second, 6));
}

std::pair<int, int> Player::diceCoordinates() const {
    std::pair<int, int> coordinates;
    switch (color) {
        case SColor::Red:
            coordinates = {2, 2};
            break;
        case SColor::Blue:
            coordinates = {8, 2};
            break;
        case SColor::Green:
            coordinates = {8, 8};
            break;
        case SColor::Yellow:
            coordinates = {2, 8};
            break;
        default:
            throw std::runtime_error("Unreachable!");
    }
    return coordinates;
}

std::pair<int, int> Player::startCoordinates() const {
    std::pair<int, int> coordinates;
    switch (color) {
        case SColor::Red:
            coordinates = {0, 4};
            break;
        case SColor::Blue:
            coordinates = {6, 0};
            break;
        case SColor::Green:
            coordinates = {10, 6};
            break;
        case SColor::Yellow:
            coordinates = {4, 10};
            break;
        default:
            throw std::runtime_error("Unreachable!");
    }
    return coordinates;
}


void Player::rollDice() {
    entities.pop_back();
    Dice dice(5, 5, GetRandomValue(1, 6));
    entities.push_back(dice);
    std::pair<int, int> start = startCoordinates();
    Piece *pieceInStart = nullptr;
    for (const auto &piece: pieces) {
        if (piece->getState() == PieceState::InStart) {
            pieceInStart = piece;
            break;
        }
    }
    if (pieceInStart != nullptr && dice.getNumber() == 6) {
        Piece *piece = board.findPiece(start);
        if (piece != nullptr) {
            if (piece->getSColor() != color) {
                actions.emplace_back(Action(*pieceInStart, start, start, PieceState::OnPath, piece));
            }
        } else {
            actions.emplace_back(Action(*pieceInStart, start, start, PieceState::OnPath, nullptr));
        }
    }
    for (const auto &piece: pieces) {
        if (piece->getState() != PieceState::InStart) {
            auto[nextCoords, newState] = board.getPath()->getNextCoordinates(*piece, dice.getNumber());
            if (nextCoords != std::pair<int, int>{-1, -1}) {
                Piece *throwOutPiece = board.findPiece(nextCoords);
                if (throwOutPiece != nullptr) {
                    if (throwOutPiece->getSColor() != color) {
                        actions.emplace_back(Action(*piece, nextCoords, nextCoords, newState, throwOutPiece));
                    }
                } else {
                    actions.emplace_back(Action(*piece, nextCoords, nextCoords, newState, nullptr));
                }
            }
        }
    }
}

Player::~Player() {
    for (auto &piece: pieces) {
        delete piece;
    }
    close(playerSockFd);
}

Player::Player(Player &&old) noexcept: color(old.color), entities(std::move(old.entities)), pieces(old.pieces),
                                       actions(std::move(old.actions)), board(old.board),
                                       playerSockFd(old.playerSockFd), cliAddr(old.cliAddr) {
    old.pieces = {nullptr, nullptr, nullptr, nullptr};
    old.playerSockFd = -1;
    bzero((char *) &old.cliAddr, sizeof(old.cliAddr));
}

bool Player::doAction(const std::pair<int, int> &clickPoint) {
    for (auto &action: actions) {
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

int Player::getActionsCount() const {
    return (int) actions.size();
}

Player &Player::operator=(Player &&other) noexcept {
    color = other.color;
    entities = std::move(other.entities);
    pieces = other.pieces;
    other.pieces = {nullptr, nullptr, nullptr, nullptr};
    actions = std::move(other.actions);
    board = other.board;
    playerSockFd = other.playerSockFd;
    other.playerSockFd = 0;
    cliAddr = other.cliAddr;
    bzero((char *) &other.cliAddr, sizeof(other.cliAddr));
    return *this;
}

const std::array<Piece *, 4> &Player::getPieces() const {
    return pieces;
}

SColor Player::getSColor() const {
    return color;
}

int Player::getPlayerSockFd() const {
    return playerSockFd;
}

void Player::quit() const {
    sendString(playerSockFd, QUIT);
}

void Player::sendMessage(const std::string &message) const {
    sendString(playerSockFd, message);
}

std::pair<bool, std::pair<int, int>> Player::getClick() const {
    sendMessage(GET_CLICK);
    if (receiveString(playerSockFd) == MOUSE_CLICK) {
        return {false, {receiveInt(playerSockFd), receiveInt(playerSockFd)}};
    }
    return {true, {-1, -1}};
}

