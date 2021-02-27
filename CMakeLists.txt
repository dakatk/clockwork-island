cmake_minimum_required(VERSION 3.17)
project(ClockworkIsland C)

set(CMAKE_C_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(ClockworkIsland
        src/Background.c include/Background.h
        src/Bounds.c include/Bounds.h
        src/Buffer.c include/Buffer.h
        src/Direction.c include/Direction.h
        src/Filter.c include/Filter.h
        src/Keyboard.c include/Keyboard.h
        src/Level.c include/Level.h
        src/LevelLoader.c include/LevelLoader.h
        src/Platform.c include/Platform.h
        src/Player.c include/Player.h
        src/Texture.c include/Texture.h
        src/Viewport.c include/Viewport.h
        src/Game.c)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})