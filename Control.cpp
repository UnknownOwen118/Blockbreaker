#include "Stats.h"
#include "Control.h"
#include "Debug.h"

int lastTimeType = 2;
int pFlag = 0;
int spaceFlag = 0;
int tasFlag = 0;
GameStats GameControl::Update(sf::RenderWindow& window, GameStats stats)
{
    while (const std::optional event = window.pollEvent())
    {
        
        // "close requested" event: we close the window
        if (event->is<sf::Event::Closed>())
               window.close();
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            if(keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::R))
        stats.Init();
    if (stats.isInGame)
    {
        if (tasFlag) stats.inStats.timeType = 0;
        if (stats.inStats.timeType)
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space))
        {
            if (stats.inStats.timeType == 1)
            {
                stats.inStats.pong.velocity = toRecCoord(stats.inStats.speed, stats.inStats.direction);
                stats.inStats.timeType = 2;
            }
            spaceFlag = 1;
        }
        else
        {
            if(spaceFlag)
                stats.inStats.timeType = lastTimeType;
            spaceFlag = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::P))
        {
            pFlag = 1;
        }
        else
        {
            if (stats.isInGame && pFlag)
            {
                if (tasFlag) stats.inStats.timeType = lastTimeType;
                tasFlag = 1 - tasFlag;
                lastTimeType = stats.inStats.timeType;
            }
            pFlag = 0;
        }
    }
    return stats;
}