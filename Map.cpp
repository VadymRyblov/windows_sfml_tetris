#include "Map.hpp"

/*============================================================================*/

Map::Map(){}

/*============================================================================*/

std::array< std::array < int, cols >, rows > & Map::getMainMatrix()
{
    return mainMatrix;
}

/*============================================================================*/

std::array< std::array < sf::Color, cols >, rows > & Map::getColoredMatrix()
{
    return coloredFiguresMatrix;
}

/*============================================================================*/

void Map::drawGrid(sf::RenderWindow & _window)
{
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            float marginInside = 4.0f; // увеличенный отступ
            sf::RectangleShape cell(sf::Vector2f(blockSize - marginInside, blockSize - marginInside));
            cell.setPosition( sf::Vector2f(
                boardStartX + x * blockSize + marginInside / 2,
                marginY + y * blockSize + marginInside / 2
            ) );
            cell.setOutlineThickness(1);
            cell.setOutlineColor(OUTLINE_COLOR);
            cell.setFillColor(GRID_COLOR);
            _window.draw(cell);
        }
    }
}

/*============================================================================*/

void Map::drawSidebar(sf::RenderWindow & _window)
{
    sf::RectangleShape sidebar( sf::Vector2f( sidebarWidth, heightWindow ) );
    sidebar.setPosition( sf::Vector2f( 0, 0 ) );
    sidebar.setFillColor( BACKGROUND_COLOR );
    _window.draw( sidebar );
}

/*============================================================================*/