#include "Display.h"
#include "Stats.h"

void GameDisplay::Draw(sf::RenderWindow& window, GameStats stats)
{
    for (int i = 0; i < stats.inStats.bricks.size(); i++)
    {
        sf::RectangleShape rectangle(stats.inStats.bricks[i].size);
        if(stats.inStats.bricks[i].type == 1)
            rectangle.setFillColor(sf::Color(127, 127, 127));
        else if (stats.inStats.bricks[i].type == 2)
            rectangle.setFillColor(sf::Color(192, 192, 192));
		else
		    rectangle.setFillColor(sf::Color(255, 255, 255));
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