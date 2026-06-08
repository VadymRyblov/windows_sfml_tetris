#include <SFML/Graphics.hpp>
#include <array>
#include <random>
#include <iostream>

#include "constants.hpp"
#include "Map.hpp"
#include "Figure.hpp"
#include "Square.hpp"
#include "Line.hpp"
#include "TFigure.hpp"

/*============================================================================*/

sf::RenderWindow window( sf::VideoMode( sf::Vector2u( widthWindow, heightWindow ) ), "Tetris" );
Map map;
bool needNewFigure { false };

/*============================================================================*/

int getRandomNumber()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 2);

    return dist(gen);
}

/*============================================================================*/

Figure * createNewFigure()
{
    int randomNumber = getRandomNumber();
    switch( randomNumber )
    {
        case 0:
            return new Square( window, map.getMainMatrix() );
        case 1:
            return new Line( window, map.getMainMatrix() );
        default:
            return new TFigure( window, map.getMainMatrix() );
    }
}

/*============================================================================*/

int main()
{
    Figure * figure = createNewFigure();
    sf::Clock clock;

    while( window.isOpen() )
    {
        sf::Time elapsed = clock.getElapsedTime();

        if( needNewFigure )
        {
            figure = createNewFigure();
            needNewFigure = false;

        }

        if ( elapsed >= sf::milliseconds(500) )
        {
            if ( figure->isPathClear( Direction::Down ) )
            {
                figure->moveFigure();
                clock.restart();
            }
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
                    case sf::Keyboard::Key::Space:
                        figure->rotateFigure();
                        continue;
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
        sf::sleep(sf::milliseconds(16));
    }

    delete figure;

    return 0;
}

/*============================================================================*/
