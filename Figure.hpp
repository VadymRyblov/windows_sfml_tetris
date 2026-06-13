#pragma once

/*============================================================================*/

#include <iostream>
#include <array>
#include "constants.hpp"

/*============================================================================*/

class Figure
{

public:

    Figure(
            sf::RenderWindow & window
        ,   std::array< std::array< int, cols >, rows > & mainMatrix
        ,   std::array< std::array< sf::Color, cols >, rows > & coloredFiguresMatrix
    );

    void markCellsOccupied();
    void markCellsNotOccupied();

    void drawFigure();
    void moveFigure();
    virtual void rotateFigure();

    void clearFilledRow( std::size_t & scoreCounter );
    void drawMainMatrix();

    void fillMainMatrix();
    void fillCurrentPiece();
    void fillColoredMatrix();

    void tempFunctionMainMatrix( ); //delete it soon
    void tempFunctionColoredMatrix( ); //delete it soon

    virtual void initializeCoordinates() = 0;
    virtual bool isPathClear( Direction direction ) = 0;

    virtual ~Figure();

protected:

    int y1, x1;
    int y2, x2;
    int y3, x3;
    int y4, x4;

    sf::RenderWindow & m_window;

    std::array< std::array< int, cols >, rows > & m_mainMatrix;
    std::array< std::array< int, cols >, rows > currentPiece{};
    std::array< std::array< sf::Color, cols >, rows > & m_coloredFiguresMatrix;

    sf::RectangleShape cell();
    Direction m_direction;
    sf::Color m_color;
};

/*============================================================================*/