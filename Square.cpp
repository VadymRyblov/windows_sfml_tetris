#include "Square.hpp"

/*============================================================================*/

Square::Square(sf::RenderWindow & window, std::array< std::array< int, cols >, rows > & mainMatrix ) : Figure(window, mainMatrix)
{
    markCellsOccupied();
}

/*============================================================================*/

void Square::markCellsOccupied()
{
    currentPiece[ m_y1 ][ m_x1 ] = 1;
    currentPiece[ m_y2 ][ m_x2 ] = 1;
    currentPiece[ m_y3 ][ m_x3 ] = 1;
    currentPiece[ m_y4 ][ m_x4 ] = 1;
}

/*============================================================================*/

void Square::markCellsNotOccupied()
{
    currentPiece[ m_y1 ][ m_x1 ] = 0;
    currentPiece[ m_y2 ][ m_x2 ] = 0;
    currentPiece[ m_y3 ][ m_x3 ] = 0;
    currentPiece[ m_y4 ][ m_x4 ] = 0;
}

/*============================================================================*/

void Square::drawFigure()
{
    float marginInside4f = 4.0f;
    float marginInside2f = 2.0f;

    sf::RectangleShape cell(sf::Vector2f(blockSize - marginInside4f, blockSize - marginInside4f));
    cell.setOutlineThickness(1);
    cell.setOutlineColor(OUTLINE_COLOR);
    cell.setFillColor(sf::Color::Green);

    cell.setPosition( sf::Vector2f(
            margin + m_x1 * blockSize + marginInside2f
        ,   margin + m_y1 * blockSize + marginInside2f
    ) );
    m_window.draw(cell);

    cell.setPosition( sf::Vector2f(
            margin + m_x2 * blockSize + marginInside2f
        ,   margin + m_y2 * blockSize + marginInside2f
    ) );
    m_window.draw(cell);

    cell.setPosition( sf::Vector2f(
            margin + m_x3 * blockSize + marginInside2f
        ,   margin + m_y3 * blockSize + marginInside2f
    ) );
    m_window.draw(cell);

    cell.setPosition( sf::Vector2f(
            margin + m_x4 * blockSize + marginInside2f
        ,   margin + m_y4 * blockSize + marginInside2f
    ) );
    m_window.draw(cell);
}

/*============================================================================*/

void Square::drawMainMatrix()
{
    float marginInside4f = 4.0f;
    float marginInside2f = 2.0f;

    // Проходим по всем ячейкам
    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            if (m_mainMatrix[y][x] == 1) // если ячейка занята
            {
                // std::cout << "Text1||||||||||||||||||" << std::endl;
                sf::RectangleShape cell(sf::Vector2f(blockSize - marginInside4f, blockSize - marginInside4f));
                cell.setOutlineThickness(1);
                cell.setOutlineColor(OUTLINE_COLOR);
                cell.setFillColor(sf::Color::Green);
                cell.setPosition( sf::Vector2f(
                    margin + x * blockSize + marginInside2f,
                    margin + y * blockSize + marginInside2f
                ) );
                m_window.draw(cell);
            }
        }
    }
}

/*============================================================================*/

void Square::tempFunction()
{
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            std::cout << m_mainMatrix[y][x] << " ";
        }
        std::cout << std::endl;
    }
}

/*============================================================================*/

void Square::moveFigure()
{
    tempFunction();
    std::cout << "========================================" << std::endl;

    markCellsNotOccupied();

    if( m_direction == Direction::Down )
    {
        m_y1++; //x1 is the same;
        m_y2++; //x2 is the same;
        m_y3++; //x3 is the same;
        m_y4++; //x4 is the same;
    }
    else if( m_direction == Direction::Right )
    {
        m_x1++; //y1 is the same;
        m_x2++; //y2 is the same;
        m_x3++; //y3 is the same;
        m_x4++; //y4 is the same;
    }
    else if( m_direction == Direction::Left )
    {
        m_x1--; //y1 is the same;
        m_x2--; //y2 is the same;
        m_x3--; //y3 is the same;
        m_x4--; //y4 is the same;
    }

    markCellsOccupied();
    drawFigure();
    tempFunction();
}

/*============================================================================*/

bool Square::isPathClear( Direction dir )
{
    m_direction = dir;

    if( m_direction == Direction::Down )
    {
        if( m_y3 == rows - 1 || m_y4 == rows - 1 || m_mainMatrix[ m_y3 + 1 ][ m_x1 ] == 1 || m_mainMatrix[ m_y4 + 1 ][ m_x2 ] == 1 )
        {
            m_mainMatrix[ m_y1 ][ m_x1 ] = 1;
            m_mainMatrix[ m_y2 ][ m_x2 ] = 1;
            m_mainMatrix[ m_y3 ][ m_x3 ] = 1;
            m_mainMatrix[ m_y4 ][ m_x4 ] = 1;

            needNewFigure = true;
            return false;
        }
    }
    else if( m_direction == Direction::Right )
    {
        if( m_x3 == cols - 1 || m_x4 == cols - 1 || m_mainMatrix[ m_y2 ][ m_x2 + 1 ] == 1 || m_mainMatrix[ m_y4 ][ m_x4 + 1 ] == 1 )
        {
            currentPiece[ m_y1 ][ m_x1 ] = 1;
            currentPiece[ m_y2 ][ m_x2 ] = 1;
            currentPiece[ m_y3 ][ m_x3 ] = 1;
            currentPiece[ m_y4 ][ m_x4 ] = 1;

            return false;
        }
    }
    else if( m_direction == Direction::Left )
    {
        if( m_x3 == 0 || m_x4 == 0 || m_mainMatrix[ m_y2 ][ m_x1 - 1 ] == 1 || m_mainMatrix[ m_y4 ][ m_x3 - 1 ] == 1 )
        {
            currentPiece[ m_y1 ][ m_x1 ] = 1;
            currentPiece[ m_y2 ][ m_x2 ] = 1;
            currentPiece[ m_y3 ][ m_x3 ] = 1;
            currentPiece[ m_y4 ][ m_x4 ] = 1;

            return false;
        }
    }

    return true;
}

/*============================================================================*/
