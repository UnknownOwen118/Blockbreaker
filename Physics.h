#include "Stats.h"
#include <random>
#include <time.h>

#pragma once

class GamePhysics
{
    static int timer;

    static GameStats LimitRacket(GameStats stats);

    static GameStats PongMove(GameStats stats);

    static int isCollideWithBrick(Pong pong, Brick brick);
    // 0 = not collide 1 = collide on the top of the brick 2 - collide on the bottom
    // 3 - left 4 - right 5 - topleft corner 6 - topright 7 - bottomleft 8 - bottomright

    static GameStats CheckDie(GameStats stats);

    static GameStats CollideWithRacket(GameStats stats);

    static GameStats CollideWithWall(GameStats stats);

    static GameStats CollideWithBrick(GameStats stats);

	static GameStats GenerateBrick(GameStats stats);

	static GameStats BrickFall(GameStats stats);
    //temperary

public:

    static GameStats Update(GameStats stats);

	static void Init();
};