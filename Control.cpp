#include "Stats.cpp"

#ifndef CONTROL

#define CONTROL
class GameControl
{
public:
    GameStats Update(sf::RenderWindow& window, GameStats stats)
    {
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Left)
                    stats.inStats.racket.pos.x -= RACKET_SPEED;
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Right)
                    stats.inStats.racket.pos.x += RACKET_SPEED;
            }
        }
        return stats;
    }
};

#endif