#include "Display.h"
#include "Stats.h"
#include "Physics.h"

void GameDisplay::DrawPredict(sf::RenderWindow& window, GameStats stats)
{
    Pong falsePong = stats.inStats.pong;
    if (stats.inStats.timeType == 1)
    {
        falsePong.velocity = toRecCoord(stats.inStats.speed, stats.inStats.direction);
    }
    for (int i = 1; i <= PREDICT_DISTANCE; i++)
    {
        falsePong = GamePhysics::PongMove(falsePong);
        falsePong = GamePhysics::CollideWithWall(falsePong);
        falsePong = GamePhysics::CollideWithBrick(falsePong, stats.inStats.bricks); \
        falsePong = GamePhysics::CollideWithRacket(falsePong, stats.inStats.racket);
        if (i % PREDICT_STEP == 0)
        {
            float newRadius = falsePong.radius * (1 - 1.0 * i / PREDICT_DISTANCE);
            sf::Vector2f deltaPos = { falsePong.radius - newRadius, falsePong.radius - newRadius };
            sf::CircleShape circle(newRadius);
            circle.setPosition(falsePong.pos + deltaPos);
            circle.setFillColor(sf::Color(0, 255, 0));
            window.draw(circle);
        }
    }
}

void GameDisplay::Draw(sf::RenderWindow& window, GameStats stats)
{
    for (int i = 0; i < stats.inStats.bricks.size(); i++)
    {
        sf::RectangleShape rectangle(stats.inStats.bricks[i].size);
        if(stats.inStats.bricks[i].type == 0)
            rectangle.setFillColor(sf::Color(STRONG_COLOR, STRONG_COLOR, STRONG_COLOR));
        else
        {
			int t = stats.inStats.bricks[i].type;
			int t1 = WEAK_COLOR + (STRONG_COLOR - WEAK_COLOR) / (NORMAL_BRICK_TYPE - 1) * (t - 1);
            rectangle.setFillColor(sf::Color(t1, t1, t1));
        }
        rectangle.setPosition(stats.inStats.bricks[i].pos);
        window.draw(rectangle);
    }
    sf::RectangleShape rectangle(stats.inStats.racket.size);
    rectangle.setPosition(stats.inStats.racket.pos);
    window.draw(rectangle);
    sf::CircleShape circle(stats.inStats.pong.radius);
    circle.setPosition(stats.inStats.pong.pos);
    window.draw(circle);
    DrawPredict(window, stats);
}

void GameDisplay::Update(sf::RenderWindow& window, GameStats stats)
{
    window.clear(sf::Color::Black);
    Draw(window, stats);
    window.display();
}