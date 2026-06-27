#pragma once

/*============================================================================*/

#include <array>
#include "constants.hpp"

/*============================================================================*/

class Map
{

public:

    Map();

    void drawGrid( sf::RenderWindow & _window );
    void drawSidebar( sf::RenderWindow & _window );

    std::array< std::array< int, cols>, rows > & getMainMatrix();
    std::array< std::array< sf::Color, cols>, rows > & getColoredMatrix();

private:

    std::array< std::array< int, cols >, rows > mainMatrix{};
    std::array< std::array< sf::Color, cols >, rows > coloredFiguresMatrix{};

};