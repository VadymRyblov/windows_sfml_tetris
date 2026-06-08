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
        if(     y4 == rows - 1
            ||  m_mainMatrix[ y4 + 1 ][ x4 ] == 1
            ||  m_mainMatrix[ y3 + 1 ][ x3 ] == 1
            ||  m_mainMatrix[ y2 + 1 ][ x2 ] == 1
            ||  m_mainMatrix[ y1 + 1 ][ x1 ] == 1
        )
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

bool Line::isPossibleHorizontalRotation()
{
    if(
        x2 <= 0 ||
        x2 + 2 >= cols
    )
    {
        return false;
    }
    else if (
            m_mainMatrix[ y2 ][ x2 - 1 ] == 0 &&
            m_mainMatrix[ y2 ][ x2 ] == 0 &&
            m_mainMatrix[ y2 ][ x2 + 1 ] == 0 &&
            m_mainMatrix[ y2 ][ x2 + 2 ] == 0
    )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Line::isPossibleVerticalRotation()
{
    if(
        m_mainMatrix[ y2 - 1 ][ x2 ] == 0 &&
        m_mainMatrix[ y2 ][ x2 ] == 0 &&
        m_mainMatrix[ y2 + 1 ][ x2 ] == 0 &&
        m_mainMatrix[ y2 + 2 ][ x2 ] == 0
    )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*============================================================================*/

void Line::rotateFigure()
{
    if( !isFigureRotated )
    {
        if ( isPossibleHorizontalRotation() )
        {
            setCoordinatesHorizontal();
            isFigureRotated = true;
        }
    }
    else
    {
        if( isPossibleVerticalRotation() )
        {
            setCoordinatesVertical();
            isFigureRotated = false;
        }
    }
}

/*============================================================================*/

void Line::setCoordinatesHorizontal()
{
    y1 = y1 + 1;
    x1 = x1 - 1;

    //y2 and x2 is our pivot

    y3 = y3 - 1;
    x3 = x3 + 1;

    y4 = y4 - 2;
    x4 = x4 + 2;
}

/*============================================================================*/

void Line::setCoordinatesVertical()
{
    y1 = y1 - 1;
    x1 = x1 + 1;

    //y2 and x2 is our pivot

    y3 = y3 + 1;
    x3 = x3 - 1;

    y4 = y2 + 2;
    x4 = x4 - 2;
}

/*============================================================================*/
