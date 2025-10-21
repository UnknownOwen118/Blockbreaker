#include "Stats.h"

void InGameStats::Init()
{
    pong.pos = { SCREEN_LENGTH / 2 - PONG_RADIUS, INIT_POSY - 2 * PONG_RADIUS };
    pong.velocity = { 0, 0 };
    pong.radius = PONG_RADIUS;
    racket.pos = { SCREEN_LENGTH / 2 - RACKET_LENGTH / 2 ,INIT_POSY };
    racket.size = { RACKET_LENGTH, RACKET_HEIGHT };
    timeType = 1;
    speed = INIT_SPEED;
    direction = 0;
}

void OutGameStats::Init()
{
    // empty for now
}

void GameStats::Init()
{
    inStats.Init();
    outStats.Init();
}