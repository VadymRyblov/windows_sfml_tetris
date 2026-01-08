#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

#include "constants.hpp"
#include "Map.hpp"
#include "Figure.hpp"
#include "Square.hpp"

/*============================================================================*/

constexpr int widthWindow = cols * blockSize + 2 * margin;
constexpr int heightWindow = rows * blockSize + 2 * margin;

sf::RenderWindow window( sf::VideoMode( widthWindow, heightWindow ), "Tetris" );

bool needNewFigure { false };

/*============================================================================*/

Figure * createNewFigure()
{
    return new Square( window );
}

/*============================================================================*/

int main()
{
    Map map;
    Figure * figure = createNewFigure();

    while( window.isOpen() )
    {
        sf::Event event;
        while( window.pollEvent( event ) )
        {
            if( event.type == sf::Event::Closed )
                window.close();

            if( needNewFigure )
            {
                figure = createNewFigure();
                needNewFigure = false;

            }

            if( event.type == sf::Event::KeyPressed )
            {
                Direction dir;

                switch( event.key.code )
                {
                    case sf::Keyboard::Down:
                        dir = Direction::Down;
                        break;
                    case sf::Keyboard::Up:
                        dir = Direction::Up;
                        break;
                    case sf::Keyboard::Left:
                        dir = Direction::Left;
                        break;
                    case sf::Keyboard::Right:
                        dir = Direction::Right;
                        break;
                    default:
                        return 0;
                }

                if ( figure->isPathClear( dir ) )
                {
                    figure->moveFigure( Direction::Down );
                }
            }
        }

        window.clear( BACKGROUND_COLOR );
        map.drawGrid( window );
        figure->drawMainMatrix();
        figure->drawFigure();
        window.display();
    }

    delete figure;

    return 0;
}

/*============================================================================*/
