#pragma once

/*============================================================================*/

#include <iostream>
#include "Figure.hpp"

/*============================================================================*/

extern bool needNewFigure; 

/*============================================================================*/

class TFigure : public Figure
{

public:

    TFigure( sf::RenderWindow & window, std::array< std::array< int, cols >, rows > & mainMatrix);

    virtual void initializeCoordinates() override;
    virtual bool isPathClear( Direction direction ) override;
    virtual void rotateFigure() override;

private:

};