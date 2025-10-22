#include "Stats.h"
#include <random>
#include <time.h>

#pragma once

class GamePhysics
{
    static int timer;

    static Brick LimitRacket(Brick racket);

	static float LimitDirection(float direction);

	static Pong LimitUnshotPong(Pong pong, Brick racket);

    static Pong PongMove(Pong pong);

    static int isCollideWithBrick(Pong pong, Brick brick);
    // 0 = not collide 1 = collide on the top of the brick 2 - collide on the bottom
    // 3 - left 4 - right 5 - topleft corner 6 - topright 7 - bottomleft 8 - bottomright

    static bool CheckDie(Pong pong);

    static Pong CollideWithRacket(Pong pong, Brick racket);

    static Pong CollideWithWall(Pong pong);

    static Pong CollideWithBrick(Pong pong, std::vector<Brick> bricks);

	static std::vector<Brick> HitBrick(Pong pong, std::vector<Brick> bricks);

	static std::vector<Brick> GenerateBrick(std::vector<Brick> bricks);

	static std::vector<Brick> BrickFall(std::vector<Brick> bricks);
    //temperary

public:

    static GameStats Update(GameStats stats);

	static void Init();
};