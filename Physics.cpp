#include "Stats.cpp"

#ifndef PHYSICS
#define PHYSICS

class GamePhysics
{
public:
    GameStats Update(sf::RenderWindow& window, GameStats stats)
    {
        if (!stats.isInGame) return stats;
        if (stats.inStats.racket.pos.x <= 0) stats.inStats.racket.pos.x = 0;
        if (stats.inStats.racket.pos.x + RACKET_LENGTH >= SCREEN_LENGTH)
            stats.inStats.racket.pos.x = SCREEN_LENGTH - RACKET_LENGTH;
        if (stats.inStats.timeType == 1)
        {
            stats.inStats.pong.pos.x = stats.inStats.racket.pos.x + RACKET_LENGTH / 2 - PONG_RADIUS;
        }

        return stats;
    }
};

#endif