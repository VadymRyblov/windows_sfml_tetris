#pragma once

/*============================================================================*/

#include <SFML/Graphics.hpp>
#include <array>
#include <random>
#include <iostream>
#include <memory>
#include <fstream>

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

    void readPlayerData();
    void savePlayerData();

    std::array<int, 5> levelSpeeds = { 500, 400, 300, 200, 100 };

    std::size_t scoreCounter { 0 };
    std::size_t gameLevel { 0 };
    std::size_t savedBestScore { 0 };
    std::size_t savedRecordTime { 0 };

    sf::RenderWindow window;
    Map map;
    std::unique_ptr<Figure> figure;

    sf::Font m_font;

    sf::Clock globalTimer;

    sf::Text scoreText; //probably it's better to use std::optional here, check later
    sf::Text levelText; //probably it's better to use std::optional here, check later
    sf::Text timeText; //probably it's better to use std::optional here, check later
    sf::Text bestScoreText; //probably it's better to use std::optional here, check later
    sf::Text recordTimeText; //probably it's better to use std::optional here, check later

    sf::RectangleShape border;
};