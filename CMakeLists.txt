cmake_minimum_required(VERSION 3.17)
project(ClockworkIsland C)

#if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/resources")
#    file(REMOVE_RECURSE "${CMAKE_CURRENT_BINARY_DIR}/resources")
#endif()
#
#file(COPY "${CMAKE_SOURCE_DIR}/resources" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(CREATE_LINK "${CMAKE_SOURCE_DIR}/resources" "${CMAKE_CURRENT_BINARY_DIR}/resources" SYMBOLIC)

set(CMAKE_C_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(ClockworkIsland
        src/engine/Background.c include/engine/Background.h
        src/engine/Buffer.c include/engine/Buffer.h
        src/engine/Direction.c include/engine/Direction.h
        src/engine/Filter.c include/engine/Filter.h
        src/engine/Keyboard.c include/engine/Keyboard.h
        src/engine/Level.c include/engine/Level.h
        src/engine/Physics.c include/engine/Physics.h
        src/engine/Platform.c include/engine/Platform.h
        src/engine/Player.c include/engine/Player.h
        src/engine/Texture.c include/engine/Texture.h
        src/engine/Viewport.c include/engine/Viewport.h
        src/AssetLoader.c include/AssetLoader.h
        src/Game.c)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})