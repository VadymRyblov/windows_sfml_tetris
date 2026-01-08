#pragma once

/*============================================================================*/

#include <iostream>
#include "Figure.hpp"

/*============================================================================*/

extern bool needNewFigure; 

/*============================================================================*/

class Square : public Figure
{

public:

    Square( sf::RenderWindow & window );

    virtual void drawFigure() override;

    virtual void drawMainMatrix() override;
    
    virtual void moveFigure( Direction directon ) override;

    virtual bool isPathClear( Direction direction ) override;

    void markCellsOccupied();
    void markCellsNotOccupied();

    void tempFunction( ); //delete me soon

private:

    int m_y1 = 0;
    int m_x1 = cols / 2 - 1;

    int m_y2 = 0;
    int m_x2 = ( cols / 2 );

    int m_y3 = 1;
    int m_x3 = cols / 2 - 1;

    int m_y4 = 1;
    int m_x4 = ( cols / 2 );
};