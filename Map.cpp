#include "Map.hpp"

/*============================================================================*/

Map::Map()
{
    mainMatrix[ 5 ][ 4 ] = 1;
}

/*============================================================================*/

std::array< std::array < int, cols >, rows > & Map::getMainMatrix()
{
    return mainMatrix;
}

/*============================================================================*/

void Map::drawGrid( sf::RenderWindow & _window )
{
    for( int y = 0; y < rows; y++ )
    {
        for( int x = 0; x < cols; x++ )
        {
            sf::RectangleShape cell( sf::Vector2f( blockSize, blockSize ) );
            cell.setPosition( margin + x * blockSize, margin + y * blockSize );
            cell.setOutlineThickness( 2 );
            cell.setOutlineColor( OUTLINE_COLOR );
            cell.setFillColor( mainMatrix[ y ] [ x ] != 0 ? sf::Color::Green : GRID_COLOR );
            _window.draw( cell );
        }
    }
}

/*============================================================================*/