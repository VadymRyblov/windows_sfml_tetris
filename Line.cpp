#include "Line.hpp"

/*============================================================================*/

Line::Line(sf::RenderWindow & window, std::array< std::array< int, cols >, rows > & mainMatrix ) : Figure(window, mainMatrix)
{
    initializeCoordinates();
    markCellsOccupied();
}

/*============================================================================*/

void Line::initializeCoordinates()
{
    y1 = 0;
    x1 = cols / 2 - 1;

    y2 = 1;
    x2 = cols / 2 - 1;

    y3 = 2;
    x3 = cols / 2 - 1;

    y4 = 3;
    x4 = cols / 2 - 1;
}

/*============================================================================*/

bool Line::isPathClear( Direction dir )
{
    m_direction = dir;

    if( m_direction == Direction::Down )
    {
        if( y4 == rows - 1 || m_mainMatrix[ y4 + 1 ][ x4 ] == 1 )
        {
            m_mainMatrix[ y1 ][ x1 ] = 1;
            m_mainMatrix[ y2 ][ x2 ] = 1;
            m_mainMatrix[ y3 ][ x3 ] = 1;
            m_mainMatrix[ y4 ][ x4 ] = 1;

            needNewFigure = true;
            return false;
        }
    }
    else if( m_direction == Direction::Right )
    {
        if(     x1 == cols - 1
            ||  x2 == cols - 1
            ||  x3 == cols - 1
            ||  x4 == cols - 1
            ||  m_mainMatrix[ y1 ][ x1 + 1 ] == 1
            ||  m_mainMatrix[ y2 ][ x2 + 1 ] == 1
            ||  m_mainMatrix[ y3 ][ x3 + 1 ] == 1
            ||  m_mainMatrix[ y4 ][ x4 + 1 ] == 1
        )
        {
            currentPiece[ y1 ][ x1 ] = 1;
            currentPiece[ y2 ][ x2 ] = 1;
            currentPiece[ y3 ][ x3 ] = 1;
            currentPiece[ y4 ][ x4 ] = 1;

            return false;
        }
    }
    else if( m_direction == Direction::Left )
    {
        if(     x1 == 0
            ||  x2 == 0
            ||  x3 == 0
            ||  x4 == 0
            ||  m_mainMatrix[ y1 ][ x1 - 1 ] == 1
            ||  m_mainMatrix[ y2 ][ x2 - 1 ] == 1
            ||  m_mainMatrix[ y3 ][ x3 - 1 ] == 1
            ||  m_mainMatrix[ y4 ][ x4 - 1 ] == 1
        )
        {
            currentPiece[ y1 ][ x1 ] = 1;
            currentPiece[ y2 ][ x2 ] = 1;
            currentPiece[ y3 ][ x3 ] = 1;
            currentPiece[ y4 ][ x4 ] = 1;

            return false;
        }
    }

    return true;
}

/*============================================================================*/
