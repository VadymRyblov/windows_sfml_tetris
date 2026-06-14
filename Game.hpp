#pragma once

/*============================================================================*/

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

class Game
{

public:

    Game();
    void run();

private:

    void infiniteLoop();
    int getRandomNumber();

    sf::Text createScoreText(const sf::Font & font);
    std::unique_ptr<Figure> createNewFigure( int randomNumber );

    void gameOverLogic();

    sf::RenderWindow window;
    Map map;
    std::unique_ptr<Figure> figure;

    sf::Font m_font;
};