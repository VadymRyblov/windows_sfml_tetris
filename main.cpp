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

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Down)
                {
                    figure->moveFigure();
                    std::cout << "std::ednl" << std::endl;
                }
            }
        }

        // Рисуем каждый кадр
        window.clear(BACKGROUND_COLOR);
        map.drawGrid(window);
        figure->drawFigure();
        window.display();
    }

    return 0;
}

/*============================================================================*/
