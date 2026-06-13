#include <SFML/Graphics.hpp>
#include <array>
#include <random>
#include <iostream>
#include <memory>

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

std::unique_ptr<Figure> createNewFigure()
{
    int randomNumber = getRandomNumber();
    switch( randomNumber )
    {
        case 0:
            return std::make_unique<Square>( window, map.getMainMatrix(), map.getColoredMatrix() );
        case 1:
            return std::make_unique<Line>( window, map.getMainMatrix(), map.getColoredMatrix() );
        case 2:
            return std::make_unique<TFigure>( window, map.getMainMatrix(), map.getColoredMatrix() );
        default:
            return 0;
    }
}

/*============================================================================*/

sf::Font & getFont()
{
    static sf::Font font;
    static bool isLoaded = false;

    if ( !isLoaded )
    {
        if ( !font.openFromFile("../fonts/DynaPuff-VariableFont_wdth,wght.ttf") )
        {
            std::cerr << "Error: Failed to load font Roboto_Condensed-Black.ttf" << std::endl;
        }
        isLoaded = true;
    }
    return font;
}

/*============================================================================*/

sf::Text createScoreText(const sf::Font & font)
{
    sf::Text text(font);
    text.setCharacterSize(26);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f( margin + 5, margin - 45 ) );

    return text;
}

/*============================================================================*/

int main()
{
    std::unique_ptr<Figure> figure = createNewFigure();
    sf::Clock clock;

    std::size_t scoreCounter = 0;
    sf::Text text = createScoreText( getFont() );

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
        figure->clearFilledRow( scoreCounter );

        text.setString("Score: " + std::to_string(scoreCounter));
        window.draw(text);

        window.display();
        sf::sleep(sf::milliseconds(16));
    }

    return 0;
}

/*============================================================================*/
