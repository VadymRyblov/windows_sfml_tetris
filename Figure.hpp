#pragma once

#include <iostream>
#include <array>
#include "constants.hpp"

class Figure
{

public:

    Figure( sf::RenderWindow & window );

    virtual void drawFigure() = 0;

    virtual void moveFigure() = 0;

protected:

    int y1, x1;
    int y2, x2;
    int y3, x3;
    int y4, x4;

    std::array< std::array< int, cols >, rows > currentPiece{};
    sf::RectangleShape cell();

    sf::RenderWindow & m_window;
};