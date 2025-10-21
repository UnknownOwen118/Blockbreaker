#include "Display.h"
#include "Stats.h"

void GameDisplay::Draw(sf::RenderWindow& window, GameStats stats)
{
    for (int i = 0; i < stats.inStats.bricks.size(); i++)
    {
        sf::RectangleShape rectangle(stats.inStats.bricks[i].size);
        rectangle.setPosition(stats.inStats.bricks[i].pos);
        window.draw(rectangle);
    }
    sf::RectangleShape rectangle(stats.inStats.racket.size);
    rectangle.setPosition(stats.inStats.racket.pos);
    window.draw(rectangle);
    sf::CircleShape circle(stats.inStats.pong.radius);
    circle.setPosition(stats.inStats.pong.pos);
    window.draw(circle);
}

void GameDisplay::Update(sf::RenderWindow& window, GameStats stats)
{
    window.clear(sf::Color::Black);
    Draw(window, stats);
    window.display();
}