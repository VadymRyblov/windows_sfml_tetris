#include "TFigure.hpp"

/*============================================================================*/

TFigure::TFigure(
        sf::RenderWindow & window
    ,   std::array< std::array< int, cols >, rows > & mainMatrix
    ,   std::array< std::array< sf::Color, cols >, rows > & coloredFiguresMatrix
) : Figure(window, mainMatrix, coloredFiguresMatrix)
{
    m_color = sf::Color::Magenta;
    initializeCoordinates();
    markCellsOccupied();
}

/*============================================================================*/

void TFigure::initializeCoordinates()
{
    y1 = 0;
    x1 = cols / 2 - 1; //up

    y2 = 1;
    x2 = cols / 2 - 1; //centre

    y3 = 1;
    x3 = cols / 2; //right

    y4 = 1;
    x4 = cols / 2 - 2; //left
}

/*============================================================================*/

bool TFigure::isPathClear( Direction dir )
{
    m_direction = dir;

    if( m_direction == Direction::Down )
    {
        if (
                y1 == rows - 1 || m_mainMatrix[ y1 + 1 ][ x1 ] == 1
            ||  y2 == rows - 1 || m_mainMatrix[ y2 + 1 ][ x2 ] == 1
            ||  y3 == rows - 1 || m_mainMatrix[ y3 + 1 ][ x3 ] == 1
            ||  y4 == rows - 1 || m_mainMatrix[ y4 + 1 ][ x4 ] == 1
        )
        {
            fillMainMatrix();
            fillColoredMatrix();

            needNewFigure = true;
            return false;
        }
    }
    else if( m_direction == Direction::Right )
    {
        if (
                x1 == cols - 1 || m_mainMatrix[ y1 ][ x1 + 1 ] == 1
            ||  x2 == cols - 1 || m_mainMatrix[ y2 ][ x2 + 1 ] == 1
            ||  x3 == cols - 1 || m_mainMatrix[ y3 ][ x3 + 1 ] == 1
            ||  x4 == cols - 1 || m_mainMatrix[ y4 ][ x4 + 1 ] == 1
        )
        {
            fillCurrentPiece();
            return false;
        }
    }
    else if( m_direction == Direction::Left )
    {
        if (
                x1 == 0 || m_mainMatrix[ y1 ][ x1 - 1 ] == 1
            ||  x2 == 0 || m_mainMatrix[ y2 ][ x2 - 1 ] == 1
            ||  x3 == 0 || m_mainMatrix[ y3 ][ x3 - 1 ] == 1
            ||  x4 == 0 || m_mainMatrix[ y4 ][ x4 - 1 ] == 1
        )
        {
            fillCurrentPiece();
            return false;
        }
    }

    return true;
}

/*============================================================================*/

void TFigure::rotateFigure()
{
    int newX1 = x2 - (y1 - y2);
    int newY1 = y2 + (x1 - x2);

    int newX3 = x2 - (y3 - y2);
    int newY3 = y2 + (x3 - x2);

    int newX4 = x2 - (y4 - y2);
    int newY4 = y2 + (x4 - x2);

    auto isInvalid = [&](int x, int y)
    {
        if (x < 0 || x >= cols || y < 0 || y >= rows)
            return true;
        if (m_mainMatrix[y][x] == 1) 
            return true;
        return false;
    };

    if (isInvalid(newX1, newY1) || isInvalid(x2, y2) || isInvalid(newX3, newY3) || isInvalid(newX4, newY4))
    {
        return; 
    }

    x1 = newX1; y1 = newY1;
    x3 = newX3; y3 = newY3;
    x4 = newX4; y4 = newY4;
}

/*============================================================================*/