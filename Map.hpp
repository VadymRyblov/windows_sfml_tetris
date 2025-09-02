#pragma once
#include <array>

#include "constants.hpp"

/*============================================================================*/

class Map
{

public:

    Map();

    std::array< std::array< int, cols>, rows > & getMainMatrix();

    void drawGrid( sf::RenderWindow & _window );

private:

    std::array< std::array< int, cols >, rows > mainMatrix{};
};