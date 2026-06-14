cmake_minimum_required(VERSION 3.15)
project(Tetris VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 COMPONENTS Graphics REQUIRED)

add_executable(Tetris main.cpp Game.cpp Map.cpp Figure.cpp Square.cpp Line.cpp TFigure.cpp)

target_link_libraries(Tetris PRIVATE SFML::Graphics)

target_compile_options(Tetris PRIVATE -Wall -Wextra -Wunused)