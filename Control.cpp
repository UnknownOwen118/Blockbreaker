#include "Stats.h"
#include "Control.h"
#include "Debug.h"

int lastTimeType = 2;
int pFlag = 0;
int spaceFlag = 0;
int tasFlag = 0;
GameStats GameControl::Update(sf::RenderWindow& window, GameStats stats)
{
    if (stats.isInGame && !stats.inStats.isPause)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
            stats.inStats.direction -= ROTATE_SPEED;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
            stats.inStats.direction += ROTATE_SPEED;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
            stats.inStats.racket.pos.x -= RACKET_SPEED;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
            stats.inStats.racket.pos.x += RACKET_SPEED;
    }
    if (stats.isInGame)
    {
        stats.inStats.isPause = tasFlag;
    }
    while (const std::optional event = window.pollEvent())
    {
        
        // "close requested" event: we close the window
        if (event->is<sf::Event::Closed>())
               window.close();
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                window.close();
            if (stats.isInGame)
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::P)
                {
                    tasFlag = 1 - tasFlag;
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
                {
                    if (stats.inStats.timeType == 1)
                    {
                        stats.inStats.pong.velocity = toRecCoord(stats.inStats.speed, stats.inStats.direction);
                        stats.inStats.timeType = 2;
                    }
                    if (tasFlag) stats.inStats.isPause = 0;
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::R)
                {
                    tasFlag = 0;
                    stats.inStats.isPause = 0;
                    stats.Init();
                }
            }
        }
    }
    return stats;
}