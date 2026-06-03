#pragma once

/*============================================================================*/

#include <iostream>
#include <array>
#include "constants.hpp"

/*============================================================================*/

class Figure
{

public:

    Figure( sf::RenderWindow & window, std::array< std::array< int, cols >, rows > & mainMatrix );

    void markCellsOccupied();
    void markCellsNotOccupied();

    void drawFigure();
    void moveFigure();

    void clearFilledRow();
    void drawMainMatrix();

    void tempFunction( ); //delete it soon

    virtual void initializeCoordinates() = 0;
    virtual bool isPathClear( Direction direction ) = 0;

    virtual ~Figure();

protected:

    int y1, x1;
    int y2, x2;
    int y3, x3;
    int y4, x4;

    std::array< std::array< int, cols >, rows > currentPiece{};
    std::array< std::array< int, cols >, rows > & m_mainMatrix;
    
    sf::RectangleShape cell();

    sf::RenderWindow & m_window;

    Direction m_direction;
};