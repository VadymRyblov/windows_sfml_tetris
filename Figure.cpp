#include "Figure.hpp"

/*============================================================================*/

Figure::Figure(
        sf::RenderWindow & window
    ,   std::array< std::array< int, cols >, rows > & mainMatrix
    ,   std::array< std::array< sf::Color, cols >, rows > & coloredFiguresMatrix
): m_window(window), m_mainMatrix(mainMatrix), m_coloredFiguresMatrix(coloredFiguresMatrix)
{
}

/*============================================================================*/

void Figure::markCellsOccupied()
{
    currentPiece[ y1 ][ x1 ] = 1;
    currentPiece[ y2 ][ x2 ] = 1;
    currentPiece[ y3 ][ x3 ] = 1;
    currentPiece[ y4 ][ x4 ] = 1;
}

/*============================================================================*/

void Figure::markCellsNotOccupied()
{
    currentPiece[ y1 ][ x1 ] = 0;
    currentPiece[ y2 ][ x2 ] = 0;
    currentPiece[ y3 ][ x3 ] = 0;
    currentPiece[ y4 ][ x4 ] = 0;
}

/*============================================================================*/

void Figure::drawFigure()
{
    float marginInside4f = 4.0f;
    float marginInside2f = 2.0f;

    sf::RectangleShape cell(sf::Vector2f(blockSize - marginInside4f, blockSize - marginInside4f));
    cell.setOutlineThickness(1);
    cell.setOutlineColor(OUTLINE_COLOR);
    cell.setFillColor( m_color );

    cell.setPosition( sf::Vector2f(
            margin + x1 * blockSize + marginInside2f
        ,   margin + y1 * blockSize + marginInside2f
    ) );
    m_window.draw(cell);

    cell.setPosition( sf::Vector2f(
            margin + x2 * blockSize + marginInside2f
        ,   margin + y2 * blockSize + marginInside2f
    ) );
    m_window.draw(cell);

    cell.setPosition( sf::Vector2f(
            margin + x3 * blockSize + marginInside2f
        ,   margin + y3 * blockSize + marginInside2f
    ) );
    m_window.draw(cell);

    cell.setPosition( sf::Vector2f(
            margin + x4 * blockSize + marginInside2f
        ,   margin + y4 * blockSize + marginInside2f
    ) );
    m_window.draw(cell);
}

/*============================================================================*/

void Figure::moveFigure()
{
    // tempFunctionMainMatrix();
    std::cout << "========================================" << std::endl;

    markCellsNotOccupied();

    if( m_direction == Direction::Down )
    {
        y1++; //x1 is the same;
        y2++; //x2 is the same;
        y3++; //x3 is the same;
        y4++; //x4 is the same;
    }
    else if( m_direction == Direction::Right )
    {
        x1++; //y1 is the same;
        x2++; //y2 is the same;
        x3++; //y3 is the same;
        x4++; //y4 is the same;
    }
    else if( m_direction == Direction::Left )
    {
        x1--; //y1 is the same;
        x2--; //y2 is the same;
        x3--; //y3 is the same;
        x4--; //y4 is the same;
    }

    markCellsOccupied();
    drawFigure();

    tempFunctionMainMatrix();
    // tempFunctionColoredMatrix();

}

/*============================================================================*/

void Figure::clearFilledRow( std::size_t & scoreCounter ) //now
{
    for (int i = 0; i < rows; ++i )
    {
        bool isRowFull = true;

        for (int j = 0; j < cols; ++j )
        {
            if (m_mainMatrix[i][j] != 1) // if row is not occupied
            {
                isRowFull = false;
            }
        }

        if( isRowFull )
        {
            for( int j = i; j >= 1; j-- )
            {
                m_mainMatrix[j] = m_mainMatrix[j-1];
            }
            scoreCounter++;
        }
    }
}

/*============================================================================*/

void Figure::drawMainMatrix()
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
                cell.setFillColor( m_coloredFiguresMatrix[y][x] );
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

void Figure::tempFunctionMainMatrix()
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

void Figure::fillMainMatrix()
{
    m_mainMatrix[ y1 ][ x1 ] = 1;
    m_mainMatrix[ y2 ][ x2 ] = 1;
    m_mainMatrix[ y3 ][ x3 ] = 1;
    m_mainMatrix[ y4 ][ x4 ] = 1;
}

/*============================================================================*/

void Figure::fillCurrentPiece()
{
    currentPiece[ y1 ][ x1 ] = 1;
    currentPiece[ y2 ][ x2 ] = 1;
    currentPiece[ y3 ][ x3 ] = 1;
    currentPiece[ y4 ][ x4 ] = 1;
}

/*============================================================================*/

void Figure::fillColoredMatrix()
{
    m_coloredFiguresMatrix[y1][x1] = m_color;
    m_coloredFiguresMatrix[y2][x2] = m_color;
    m_coloredFiguresMatrix[y3][x3] = m_color;
    m_coloredFiguresMatrix[y4][x4] = m_color;
}

/*============================================================================*/

void Figure::tempFunctionColoredMatrix()
{
    std::cout << "This is my Colored matrix:" << std::endl;
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            std::cout << "("
                << static_cast<int>(m_coloredFiguresMatrix[y][x].r) << ","
                << static_cast<int>(m_coloredFiguresMatrix[y][x].g) << ") ";
        }
        std::cout << std::endl;
    }
}

/*============================================================================*/

void Figure::rotateFigure(){}

/*============================================================================*/

Figure::~Figure(){}

/*============================================================================*/