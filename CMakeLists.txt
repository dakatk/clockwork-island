cmake_minimum_required(VERSION 3.19)
project(ClockworkIsland_NewEngine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(ClockworkIsland_NewEngine src/Game.cpp
        include/engine/BoundingBox.h src/engine/BoundingBox.cpp
        include/engine/Texture.h src/engine/Texture.cpp
        include/engine/Viewport.h src/engine/Viewport.cpp
        include/engine/Player.h src/engine/Player.cpp
        include/engine/Tile.h src/engine/Tile.cpp
        include/engine/Background.h src/engine/Background.cpp
        include/engine/Sprite.h src/engine/Sprite.cpp
        include/engine/Input.h src/engine/Input.cpp
        include/engine/Window.h src/engine/Window.cpp
        include/game/Level.h src/game/Level.cpp
        include/game/Platform.h src/game/Platform.cpp
        include/game/Robot.h src/game/Robot.cpp
        include/game/Filter.h src/game/Filter.cpp
        include/game/Direction.h src/game/Direction.cpp
        include/game/Assets.h src/game/Assets.cpp include/engine/Timer.h src/engine/Timer.cpp)

file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::Image m)