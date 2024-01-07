cmake_minimum_required(VERSION 3.14)
project(algorithms)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp
        src/Game/Game.cpp
        src/Game/Game.h
        src/World/World.cpp
        src/World/World.h
        src/Tile/Tile.cpp
        src/Tile/Tile.h
        src/Pathfinder/Graph/Graph.cpp
        src/Pathfinder/Graph/Graph.h
        src/Pathfinder/StatePathfinder.cpp
        src/Pathfinder/StatePathfinder.h
        src/AssetsRepository/AssetsRepository.cpp
        src/AssetsRepository/AssetsRepository.h)
add_executable(algorithms ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(algorithms sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

file(COPY resources DESTINATION .)