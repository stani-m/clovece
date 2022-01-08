cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(clovece)

set(CMAKE_CXX_STANDARD 17)

# Set this to the minimal version you want to support
find_package(raylib 3.0 QUIET) # Let CMake search for a raylib-config.cmake

# You could change the QUIET above to REQUIRED and remove this if() clause
# This part downloads raylib and builds it if it's not installed on your system
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)

    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz
    )

    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)

        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

        # build raylib
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

    endif()

endif()

# This is the main part:

add_executable(clovece main.cpp server/Entity.cpp server/Entity.h server/SColor.h server/Piece.cpp server/Piece.h server/Tile.cpp server/Tile.h server/Arrow.cpp server/Arrow.h server/Direction.h server/Board.cpp server/Board.h server/Path.cpp server/Path.h server/Player.cpp server/Player.h server/Dice.cpp server/Dice.h server/Game.cpp server/Game.h server/TurnState.h server/Dot.cpp server/Dot.h server/PieceState.h server/Action.cpp server/Action.h server/Turn.cpp server/Turn.h client/Client.cpp client/Client.h common/utils.h common/utils.cpp common/messages.h)
#set(raylib_VERBOSE 1)
target_link_libraries(clovece raylib pthread)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(clovece "-framework IOKit")
    target_link_libraries(clovece "-framework Cocoa")
    target_link_libraries(clovece "-framework OpenGL")
endif()

# That's it! You should have an example executable that you can run. Have fun!
