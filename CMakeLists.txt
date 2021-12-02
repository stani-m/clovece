cmake_minimum_required(VERSION 3.7)
project(clovece)

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)

add_executable(clovece main.cpp game/Entity.cpp game/Entity.h game/Color.h game/Piece.cpp game/Piece.h game/Tile.cpp game/Tile.h game/Arrow.cpp game/Arrow.h game/Direction.h)
target_link_libraries(clovece SDL2::Main)
