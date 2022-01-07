cmake_minimum_required(VERSION 3.7)
project(clovece)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)

add_executable(clovece main.cpp server/Entity.cpp server/Entity.h server/Color.h server/Piece.cpp server/Piece.h server/Tile.cpp server/Tile.h server/Arrow.cpp server/Arrow.h server/Direction.h server/Board.cpp server/Board.h server/Path.cpp server/Path.h server/Player.cpp server/Player.h server/Dice.cpp server/Dice.h server/Game.cpp server/Game.h server/TurnState.h server/Dot.cpp server/Dot.h server/PieceState.h server/Action.cpp server/Action.h server/Turn.cpp server/Turn.h client/Client.cpp client/Client.h common/utils.h common/utils.cpp common/messages.h)
target_link_libraries(clovece SDL2::Main pthread)
