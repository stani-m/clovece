cmake_minimum_required(VERSION 3.7)
project(clovece)

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)

add_executable(clovece main.cpp game/Entity.cpp game/Entity.h game/Color.h game/Piece.cpp game/Piece.h game/Tile.cpp game/Tile.h game/Arrow.cpp game/Arrow.h game/Direction.h game/Board.cpp game/Board.h game/Path.cpp game/Path.h game/Player.cpp game/Player.h game/Dice.cpp game/Dice.h game/Game.cpp game/Game.h game/TurnState.h game/Dot.cpp game/Dot.h game/PieceState.h game/Action.cpp game/Action.h game/Turn.cpp game/Turn.h)
target_link_libraries(clovece SDL2::Main)
