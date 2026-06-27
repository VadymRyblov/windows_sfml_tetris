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

/*============================================================================*/

enum class ColorsFigure
{
    NoColored,
    Yellow,
    Green,
    Magenta
};

/*============================================================================*/

constexpr int cols = 10;
constexpr int rows = 20;
constexpr int blockSize = 36;

constexpr int marginY = 40;
constexpr int marginRight = 240;

//Left text
constexpr int sidebarWidth = 240;

//Sidebar and game gap
constexpr int sidebarGap = 20;

constexpr int boardStartX = sidebarWidth + sidebarGap;

constexpr int boardWidth = cols * blockSize;
constexpr int boardHeight = rows * blockSize;

// Windows size
constexpr int widthWindow = sidebarWidth + sidebarGap + boardWidth + marginRight;
constexpr int heightWindow = marginY + boardHeight + marginY;

//Interface colors
const sf::Color BACKGROUND_COLOR(40, 0, 60); 
const sf::Color GRID_COLOR(30, 30, 100); 
const sf::Color OUTLINE_COLOR(80, 80, 150); 

/*============================================================================*/