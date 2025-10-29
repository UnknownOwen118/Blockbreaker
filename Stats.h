#include <vector>
#include "Basic.h"
#include "Elements.h"

class InGameStats
{
    public:
        std::vector<Brick> bricks;
        Pong pong;
        Brick racket;
        float direction, speed;
        int timeType = 1;
        int isPause = 0;
        void Init();
        void GenerateBlock();
};
//1 - shooting 2 - flying

class OutGameStats
{
public:
    void Init();
};

class GameStats
{
    
public:
    bool isInGame = 1;
    InGameStats inStats;
    OutGameStats outStats;

    void Init();
    void Reset();
};
#pragma once
