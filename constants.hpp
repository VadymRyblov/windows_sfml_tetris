#pragma once
#include <SFML/Graphics.hpp>

/*============================================================================*/

enum class Direction
{
    Up,
    Left,
    Right,
    Down 
};

constexpr int cols = 10;
constexpr int rows = 20;

constexpr int blockSize = 36;
constexpr int margin = 36;

constexpr int widthWindow = cols * blockSize + 2 * margin;
constexpr int heightWindow = rows * blockSize + 2 * margin;

//Colors
const sf::Color BACKGROUND_COLOR(40, 0, 60); //add inline but later
const sf::Color GRID_COLOR(30, 30, 100);
const sf::Color OUTLINE_COLOR(80, 80, 150);

/*============================================================================*/