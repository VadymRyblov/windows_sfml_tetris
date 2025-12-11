#pragma once

#include <iostream>
#include "Figure.hpp"

class Square : public Figure
{

public:

    Square(sf::RenderWindow & window);

    void setStartPosition();
    virtual void drawFigure();

    virtual void moveFigure();

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