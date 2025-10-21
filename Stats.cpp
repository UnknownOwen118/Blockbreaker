#include <vector>
#include "Basic.cpp"
#include "Elements.cpp"

#ifndef STATS
#define STATS
class InGameStats
{
public:
    std::vector<Brick> bricks;
    Pong pong;
    Brick racket;
    int timeType;
    // 0 - "animation time" 1 - "shooting" 2 - "normal gameplay"
    void Init()
    {
        pong.pos = { SCREEN_LENGTH / 2 - PONG_RADIUS, INIT_POSY - 2 * PONG_RADIUS };
        pong.radius = PONG_RADIUS;
        racket.pos = { SCREEN_LENGTH / 2 - RACKET_LENGTH / 2 ,INIT_POSY };
        racket.size = { RACKET_LENGTH, RACKET_HEIGHT };
        timeType = 1;
    }
};

class OutGameStats
{
public:
    void Init()
    {
    }
};

class GameStats
{
public:
    bool isInGame = 1;
    InGameStats inStats;
    OutGameStats outStats;

    void Init()
    {
        inStats.Init();
        outStats.Init();
    }

};
#endif