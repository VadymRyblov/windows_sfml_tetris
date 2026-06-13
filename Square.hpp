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

    Square(
            sf::RenderWindow & window
        ,   std::array< std::array< int, cols >, rows > & mainMatrix
        ,   std::array< std::array< sf::Color, cols >, rows > & coloredFiguresMatrix
    );

    virtual void initializeCoordinates() override;
    virtual bool isPathClear( Direction direction ) override;

private:

};