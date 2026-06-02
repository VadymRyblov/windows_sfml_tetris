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

sf::RenderWindow window( sf::VideoMode( sf::Vector2u( widthWindow, heightWindow ) ), "Tetris" );
Map map;

bool needNewFigure { false };

/*============================================================================*/

Figure * createNewFigure()
{
    return new Square( window, map.getMainMatrix() );
}

/*============================================================================*/

int main()
{
    Figure * figure = createNewFigure();

    while( window.isOpen() )
    {
        if( needNewFigure )
        {
            figure = createNewFigure();
            needNewFigure = false;

        }

        while( const std::optional event = window.pollEvent() )
        {
            if( event->is<sf::Event::Closed>() )
                window.close();


            if( const auto* keyPressed = event->getIf<sf::Event::KeyPressed>() )
            {
                Direction dir;

                switch( keyPressed->code )
                {
                    case sf::Keyboard::Key::Down:
                        dir = Direction::Down;
                        break;
                    case sf::Keyboard::Key::Up:
                        dir = Direction::Up;
                        break;
                    case sf::Keyboard::Key::Left:
                        dir = Direction::Left;
                        break;
                    case sf::Keyboard::Key::Right:
                        dir = Direction::Right;
                        break;
                    default:
                        return 0;
                }

                if ( figure->isPathClear( dir ) )
                {
                    figure->moveFigure();
                }
            }
        }

        window.clear( BACKGROUND_COLOR );
        map.drawGrid( window );
        figure->drawMainMatrix();
        figure->drawFigure();
        figure->clearFilledRow();
        window.display();
    }

    delete figure;

    return 0;
}

/*============================================================================*/
