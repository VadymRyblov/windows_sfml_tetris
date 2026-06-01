#include "Figure.hpp"

/*============================================================================*/

Figure::Figure( sf::RenderWindow & window, std::array< std::array< int, cols >, rows > & mainMatrix ): m_window(window), m_mainMatrix(mainMatrix)
{
}

/*============================================================================*/
