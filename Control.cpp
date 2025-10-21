#include "Stats.h"
#include "Control.h"

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
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
            stats.inStats.direction -= ROTATE_SPEED;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
            stats.inStats.direction += ROTATE_SPEED;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
            stats.inStats.racket.pos.x -= RACKET_SPEED;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
            stats.inStats.racket.pos.x += RACKET_SPEED;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space))
            if (stats.isInGame && stats.inStats.timeType == 1)
            {
                stats.inStats.pong.velocity = toRecCoord(stats.inStats.speed, stats.inStats.direction);
                stats.inStats.timeType = 2;
            }
    }
    return stats;
}