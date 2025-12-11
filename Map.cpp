#include "Map.hpp"

/*============================================================================*/

Map::Map()
{

}

/*============================================================================*/

std::array< std::array < int, cols >, rows > & Map::getMainMatrix()
{
    return mainMatrix;
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
            cell.setPosition(
                margin + x * blockSize + marginInside / 2,
                margin + y * blockSize + marginInside / 2
            );
            cell.setOutlineThickness(1);
            cell.setOutlineColor(OUTLINE_COLOR);
            cell.setFillColor(GRID_COLOR);
            _window.draw(cell);
        }
    }
}

/*============================================================================*/