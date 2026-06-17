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

    sf::Text settingsText( size_t x, size_t y );
    std::unique_ptr<Figure> createNewFigure( int randomNumber );

    void gameOverLogic();
    void gameLevelLogic();

    std::array<int, 5> levelSpeeds = { 500, 400, 300, 200, 100 };
    std::size_t scoreCounter { 0 };
    size_t gamelevel { 0 };

    sf::RenderWindow window;
    Map map;
    std::unique_ptr<Figure> figure;

    sf::Font m_font;

    sf::Text scoreText; //probably it's better to use std::optional here, check later
    sf::Text levelText; //probably it's better to use std::optional here, check later
};