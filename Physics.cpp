#include "Physics.h"
#include "Stats.h"
#include <cmath>

GameStats GamePhysics::LimitRacket(GameStats stats)
{
    if (stats.inStats.racket.pos.x <= 0) stats.inStats.racket.pos.x = 0;
    if (stats.inStats.racket.pos.x + RACKET_LENGTH >= SCREEN_LENGTH)
        stats.inStats.racket.pos.x = SCREEN_LENGTH - RACKET_LENGTH;
    if (stats.inStats.timeType == 1)
    {
        if (stats.inStats.direction <= -MAX_ROTATION) stats.inStats.direction = -MAX_ROTATION;
        if (stats.inStats.direction >= MAX_ROTATION) stats.inStats.direction = MAX_ROTATION;
        stats.inStats.pong.pos.x = stats.inStats.racket.pos.x + RACKET_LENGTH / 2 - stats.inStats.pong.radius;
    }
    return stats;
}

GameStats GamePhysics::CollideWithWall(GameStats stats)
{
    if (stats.inStats.pong.pos.x < 0)
    {
        stats.inStats.pong.velocity.x = -stats.inStats.pong.velocity.x;
        stats.inStats.pong.pos.x = 0;
    }
    if (stats.inStats.pong.pos.x > SCREEN_LENGTH - 2 * stats.inStats.pong.radius)
    {
        stats.inStats.pong.velocity.x = -stats.inStats.pong.velocity.x;
        stats.inStats.pong.pos.x = SCREEN_LENGTH - 2 * stats.inStats.pong.radius;
    }
    if (stats.inStats.pong.pos.y < 0)
    {
        stats.inStats.pong.velocity.y = -stats.inStats.pong.velocity.y;
        stats.inStats.pong.pos.y = 0;
    }
    return stats;
}

GameStats GamePhysics::PongMove(GameStats stats)
{
    if (stats.inStats.timeType == 2)
        stats.inStats.pong.pos += stats.inStats.pong.velocity;
    return stats;
}

int GamePhysics::isCollideWithBrick(Pong pong, Brick brick)
{
    float r = pong.radius;
    float x = pong.pos.x + r;
    float y = pong.pos.y + r;

    float y1 = brick.pos.y;
    float y2 = y1 + brick.size.y;
    float x1 = brick.pos.x;
    float x2 = x1 + brick.size.x;

    if (x >= x1 && x <= x2)
    {
        if (y + r >= y1 && y <= (y1 + y2) / 2) return 1;
        if (y - r <= y2 && y >= (y1 + y2) / 2) return 2;
    }
    if (y >= y1 && y <= y2)
    {
        if (x + r >= x1 && x <= (x1 + x2) / 2) return 3;
        if (x - r <= x2 && x >= (x1 + x2) / 2) return 4;
    }
    if (x <= x1 && y <= y1 && Distance({ x, y }, { x1, y1 }) <= r) return 5;
    if (x >= x2 && y <= y1 && Distance({ x, y }, { x2, y1 }) <= r) return 6;
    if (x <= x1 && y >= y2 && Distance({ x, y }, { x1, y2 }) <= r) return 7;
    if (x >= x2 && y >= y2 && Distance({ x, y }, { x2, y2 }) <= r) return 8;

    return 0;
    // 0 = not collide 1 = collide on the top of the brick 2 - collide on the bottom
    // 3 - left 4 - right 5 - topleft corner 6 - topright 7 - bottomleft 8 - bottomright
}

GameStats GamePhysics::CollideWithRacket(GameStats stats)
{
    int flag = isCollideWithBrick(stats.inStats.pong, stats.inStats.racket);
    if (!flag) return stats;
    float dx = 2 * (stats.inStats.pong.pos.x + stats.inStats.pong.radius -
        stats.inStats.racket.pos.x - stats.inStats.racket.size.x / 2) / stats.inStats.racket.size.x;
    stats.inStats.pong.velocity = toRecCoord(stats.inStats.speed, dx * MAX_ROTATION);
    if (flag == 2 || flag == 7 || flag == 8)
        stats.inStats.pong.velocity.y = -stats.inStats.pong.velocity.y;
    return stats;
}

GameStats GamePhysics::CheckDie(GameStats stats)
{
    if (stats.inStats.pong.pos.y >= SCREEN_HEIGHT)
    {
        stats.inStats.timeType = 1;
        stats.inStats.Init();
    }
    return stats;
}

GameStats GamePhysics::Update(GameStats stats)
{
    if (!stats.isInGame) return stats;
    stats = LimitRacket(stats);
    stats = PongMove(stats);
    stats = CollideWithWall(stats);
    stats = CollideWithRacket(stats);
    stats = CheckDie(stats);
    return stats;
}