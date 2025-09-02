#include <SFML/Graphics.hpp>
#include <array>

#include "constants.hpp"
#include "Map.hpp"

/*============================================================================*/

int main()
{
    constexpr int widthWindow = cols * blockSize + 2 * margin;
    constexpr int heightWindow = rows * blockSize + 2 * margin;

    sf::RenderWindow window( sf::VideoMode( widthWindow, heightWindow ), "Tetris" );
    Map map;

    while( window.isOpen() )
    {
        sf::Event event;
        while( window.pollEvent( event ) )
        {
            if ( event.type == sf::Event::Closed )
                window.close();
        }

        window.clear( BACKGROUND_COLOR );
        map.drawGrid( window );
        window.display();
    }

    return 0;
}

/*============================================================================*/
