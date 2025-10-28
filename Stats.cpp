#include "Stats.h"

void InGameStats::GenerateBlock()
{
    for (int i = 0; i < BRICK_ROWS; i++)
    {
        for (int j = 0; j < BRICK_COLUMNS; j++)
        {
            Brick brick;
            brick.size = { BRICK_LENGTH, BRICK_HEIGHT };
            brick.pos = { j * BRICK_LENGTH, i * BRICK_HEIGHT + TOP_OFFSET };
            brick.type = (i + j) % 5; // just a sample pattern
            if (i == BRICK_ROWS - 1 && (j == 5 || j == 4)) continue;
            bricks.push_back(brick);
        }
    }
}

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
    inStats.GenerateBlock();
    inStats.Init();
    outStats.Init();
}
void GameStats::Reset()
{
    inStats.Init();
    outStats.Init();
}