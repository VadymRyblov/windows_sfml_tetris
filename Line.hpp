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

    Line(
            sf::RenderWindow & window
        ,   std::array< std::array< int, cols >, rows > & mainMatrix
        ,   std::array< std::array< sf::Color, cols >, rows > & coloredFiguresMatrix
    );

    virtual void initializeCoordinates() override;
    virtual bool isPathClear( Direction direction ) override;
    virtual void rotateFigure() override;

private:

    bool isFigureRotated = { false };

    bool isPossibleHorizontalRotation();
    bool isPossibleVerticalRotation();

    void setCoordinatesHorizontal();
    void setCoordinatesVertical();

};