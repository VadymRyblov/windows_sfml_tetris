#include "Game.hpp"

/*============================================================================*/

bool needNewFigure { false };

/*============================================================================*/

Game::Game() :
        window( sf::VideoMode( sf::Vector2u( widthWindow, heightWindow ) ), "Tetris" )
    ,   scoreText(m_font)
    ,   levelText(m_font)
    ,   timeText(m_font)
    ,   bestScoreText(m_font)
    ,   recordTimeText(m_font)
{
    if( !m_font.openFromFile("../fonts/DynaPuff-VariableFont_wdth,wght.ttf") )
    {
        std::cerr << "Error: Failed to load font" << std::endl;
    }
    figure = createNewFigure( getRandomNumber() );
    readPlayerData();

    size_t sidebarX = 50;

    //Current game
    scoreText      = settingsText( sidebarX, 120 );
    levelText      = settingsText( sidebarX, 165 );
    timeText       = settingsText( sidebarX, 210 );

    //Records
    bestScoreText  = settingsText( sidebarX, 320 );
    recordTimeText = settingsText( sidebarX, 365 );

    border.setSize( sf::Vector2f( sidebarWidth - 22, boardHeight - 350 ) );
    border.setPosition( sf::Vector2f( 40, marginY + 3 ) );
    border.setFillColor( sf::Color::Transparent );
    border.setOutlineColor( sf::Color::Cyan );
    border.setOutlineThickness( 2 );
}

/*============================================================================*/

void Game::run()
{
    infiniteLoop();
}

/*============================================================================*/

void Game::infiniteLoop()
{
    sf::Clock fallingTimer;

    while( window.isOpen() )
    {
        sf::Time fallingTimerElapsed = fallingTimer.getElapsedTime();

        gameOverLogic();
        gameLevelLogic();

        if( needNewFigure )
        {
            figure = createNewFigure( getRandomNumber() );
            needNewFigure = false;
        }

        if ( fallingTimerElapsed >= sf::milliseconds( levelSpeeds[ gameLevel ] ) )
        {
            if ( figure->isPathClear( Direction::Down ) )
            {
                figure->moveFigure();
                fallingTimer.restart();
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
                        return;
                }

                if ( figure->isPathClear( dir ) )
                {
                    figure->moveFigure();
                }
            }
        }

        window.clear( BACKGROUND_COLOR );
        map.drawGrid( window );
        map.drawSidebar( window );
        figure->drawMainMatrix();
        figure->drawFigure();
        figure->clearFilledRow( scoreCounter );

        int seconds = globalTimer.getElapsedTime().asSeconds();

        scoreText.setString("Score: " + std::to_string(scoreCounter));
        levelText.setString("Level: " + std::to_string(gameLevel + 1));
        timeText.setString("Time: " + std::to_string(seconds));
        bestScoreText.setString("Best score: " + std::to_string(savedBestScore));
        recordTimeText.setString("Time: " + std::to_string(savedRecordTime) + "s");

        window.draw(border);
        window.draw(scoreText);
        window.draw(levelText);
        window.draw(timeText);
        window.draw(bestScoreText);
        window.draw(recordTimeText);

        window.display();
        sf::sleep(sf::milliseconds(16));
    }
}

/*============================================================================*/

int Game::getRandomNumber()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 2);

    return dist(gen);
}

/*============================================================================*/

sf::Text Game::settingsText( size_t x, size_t y )
{
    sf::Text text( m_font );
    text.setCharacterSize(26);
    text.setFillColor(sf::Color::White);
    text.setPosition( 
        sf::Vector2f( 
            static_cast<float>(x)
        ,   static_cast<float>(y) )
    );

    return text;
}

/*============================================================================*/

std::unique_ptr<Figure> Game::createNewFigure( int randomNumber )
{
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

void Game::gameOverLogic()
{
    if(
            map.getMainMatrix()[ 0 ][ cols / 2 - 1 ] == 1
        ||  map.getMainMatrix()[ 0 ][ cols / 2 ] == 1
    )
    {
        savePlayerData();

        sf::Text gameOverText( m_font );
        gameOverText.setString("Game Over");
        gameOverText.setCharacterSize(60);
        gameOverText.setFillColor(sf::Color::Red);

        sf::FloatRect textRect = gameOverText.getLocalBounds();
        
        gameOverText.setOrigin( sf::Vector2f(
                textRect.position.x + textRect.size.x / 2.0f
            ,   textRect.position.y + textRect.size.y / 2.0f
        ));
        gameOverText.setPosition(sf::Vector2f( widthWindow / 2.0f, heightWindow / 2.0f ));

        while( window.isOpen() )
        {
            while( const std::optional event = window.pollEvent() )
            {
                if( event->is<sf::Event::Closed>() )
                    window.close();
            }

            window.clear( BACKGROUND_COLOR );
            window.draw( gameOverText );
            window.display();

            sf::sleep(sf::milliseconds(16));
        }
    }
}

/*============================================================================*/

void Game::gameLevelLogic()
{
    if( scoreCounter >= 3 && scoreCounter < 6 )
    {
        gameLevel = 1;
    }
    else if( scoreCounter >= 6 && scoreCounter < 9 )
    {
        gameLevel = 2;
    }
    else if( scoreCounter >= 9 && scoreCounter < 12 )
    {
        gameLevel = 3;
    }
    else if( scoreCounter >= 12 )
    {
        gameLevel = 4;
    }
}

/*============================================================================*/

void Game::readPlayerData()
{
    std::ifstream file("../playerData.txt");
    if( file.is_open() )
    {
        std::string label;

        file >> label >> label >> savedBestScore;
        file >> label >> label >> savedRecordTime;
    }
    else
    {
        std::cerr << "Error: Failed to open playerData.txt" << std::endl;
        return;
    }
}

/*============================================================================*/

void Game::savePlayerData()
{
    if (scoreCounter > savedBestScore)
    {
        std::ofstream file("../playerData.txt");
        if (file.is_open())
        {
            int currentSeconds = globalTimer.getElapsedTime().asSeconds();

            file << "Best score: " << scoreCounter << "\n";
            file << "Record time: " << currentSeconds << "s" << "\n";
        }
    }
}

/*============================================================================*/