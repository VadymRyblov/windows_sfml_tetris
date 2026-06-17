#include "Game.hpp"

/*============================================================================*/

bool needNewFigure { false };

/*============================================================================*/

Game::Game() :
        window( sf::VideoMode( sf::Vector2u( widthWindow, heightWindow ) ), "Tetris" )
    ,   scoreText(m_font)
    ,   levelText(m_font)
{
    if( !m_font.openFromFile("../fonts/DynaPuff-VariableFont_wdth,wght.ttf") )
    {
        std::cerr << "Error: Failed to load font" << std::endl;
    }
    figure = createNewFigure( getRandomNumber() );

    scoreText = settingsText( 5, 45 );
    levelText = settingsText( 150, 45 );
}

/*============================================================================*/

void Game::run()
{
    infiniteLoop();
}

/*============================================================================*/

void Game::infiniteLoop()
{
    sf::Clock clock;

    while( window.isOpen() )
    {
        sf::Time elapsed = clock.getElapsedTime();

        gameOverLogic();
        gameLevelLogic();

        if( needNewFigure )
        {
            figure = createNewFigure( getRandomNumber() );
            needNewFigure = false;
        }

        if ( elapsed >= sf::milliseconds( levelSpeeds[ gamelevel ] ) )
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
        figure->drawMainMatrix();
        figure->drawFigure();
        figure->clearFilledRow( scoreCounter );

        scoreText.setString("Score: " + std::to_string(scoreCounter));
        levelText.setString("Level: " + std::to_string(gamelevel + 1));

        window.draw(scoreText);
        window.draw(levelText);

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
    text.setPosition(sf::Vector2f( margin + x, margin - y ) );

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
        gamelevel = 1;
    }
    else if( scoreCounter >= 6 && scoreCounter < 9 )
    {
        gamelevel = 2;
    }
    else if( scoreCounter >= 9 && scoreCounter < 12 )
    {
        gamelevel = 3;
    }
    else if( scoreCounter >= 12 )
    {
        gamelevel = 4;
    }
}

/*============================================================================*/