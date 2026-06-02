#include "Figure.hpp"

/*============================================================================*/

Figure::Figure( sf::RenderWindow & window, std::array< std::array< int, cols >, rows > & mainMatrix ): m_window(window), m_mainMatrix(mainMatrix)
{
}

/*============================================================================*/

void Figure::clearFilledRow()
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
        }
    }
}

/*============================================================================*/

Figure::~Figure() {}
