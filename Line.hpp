#pragma once

/*============================================================================*/

#include <iostream>
#include "Figure.hpp"

/*============================================================================*/

extern bool needNewFigure; 

/*============================================================================*/

class Line : public Figure
{

public:

    Line( sf::RenderWindow & window, std::array< std::array< int, cols >, rows > & mainMatrix);

    virtual void initializeCoordinates() override;
    virtual bool isPathClear( Direction direction ) override;

private:

};