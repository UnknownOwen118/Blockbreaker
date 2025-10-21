#include "Physics.h"
#include "Stats.h"
#include <cmath>

int GamePhysics::timer = 0;

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
    if (x <= x1 && y >= y2 && Distance({ x, y }, { x1, y2 }) <= r) return 8;
    if (x >= x2 && y >= y2 && Distance({ x, y }, { x2, y2 }) <= r) return 7;

    return 0;
    // 0 = not collide 1 = collide on the top of the brick 2 - collide on the bottom
    // 3 - left 4 - right 5 - topleft corner 6 - topright 7 - bottomright 8 - bottomleft
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

GameStats GamePhysics::CollideWithBrick(GameStats stats)
{
    for (int i = 0; i < stats.inStats.bricks.size(); i++)
    {
        int flag = isCollideWithBrick(stats.inStats.pong, stats.inStats.bricks[i]);
        if (!flag) continue;
        if (flag == 1 || flag == 2) 
            stats.inStats.pong.velocity.y = -stats.inStats.pong.velocity.y;
        else if (flag == 3 || flag == 4)
            stats.inStats.pong.velocity.x = -stats.inStats.pong.velocity.x;
        else
        {
            /*
            sf::Vector2f corner;
            if (flag == 5) corner = stats.inStats.bricks[i].pos;
            else if (flag == 6) corner = { stats.inStats.bricks[i].pos.x + stats.inStats.bricks[i].size.x, stats.inStats.bricks[i].pos.y };
            else if (flag == 7) corner = { stats.inStats.bricks[i].pos.x, stats.inStats.bricks[i].pos.y + stats.inStats.bricks[i].size.y };
            else corner = { stats.inStats.bricks[i].pos.x + stats.inStats.bricks[i].size.x, stats.inStats.bricks[i].pos.y + stats.inStats.bricks[i].size.y };
            sf::Vector2f normal = stats.inStats.pong.pos + sf::Vector2f(stats.inStats.pong.radius, stats.inStats.pong.radius) - corner;
            float length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
            normal /= length;
            float dot = stats.inStats.pong.velocity.x * normal.x + stats.inStats.pong.velocity.y * normal.y;
            stats.inStats.pong.velocity -= 2 * dot * normal;
            */
			//以上有bug。如果球溜边碰撞，法线计算会出问题，导致球卡在砖块里
			float direction = flag * PI / 2 - PI * 3.f + (rand() % RAND_PRECISION) / (RAND_PRECISION * 1.0f) * (PI / 2.f);
			stats.inStats.pong.velocity = toRecCoord(stats.inStats.speed, direction);
		}
		stats = PongMove(stats);
        if (stats.inStats.bricks[i].type == 1)
        {
            stats.inStats.bricks.erase(stats.inStats.bricks.begin() + i);
            i--;
        }
		else if (stats.inStats.bricks[i].type == 2)
        {
			stats.inStats.bricks[i].type = 1;
        }
    }
	return stats;
}

GameStats GamePhysics::GenerateBrick(GameStats stats)
{
    Brick brick;
    brick.pos = { (rand() % (SCREEN_LENGTH - BLOCK_LENGTH)) * 1.0f, 0.0f};
    brick.size = { BLOCK_LENGTH, BLOCK_HEIGHT };
    brick.type = rand() % 3;
    stats.inStats.bricks.push_back(brick);
    return stats;
}

GameStats GamePhysics::BrickFall(GameStats stats)
{
    for (int i = 0; i < stats.inStats.bricks.size(); i++)
    {
        stats.inStats.bricks[i].pos.y += FALL_SPEED;
        if (stats.inStats.bricks[i].pos.y > SCREEN_HEIGHT)
        {
            stats.inStats.bricks.erase(stats.inStats.bricks.begin() + i);
            i--;
        }
    }
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
    stats = PongMove(stats);
	//这里必须先移动球，再检测碰撞，否则发球时立刻碰撞会出问题
    stats = LimitRacket(stats);
    if (timer % 20 == 0)
    {
        stats = GenerateBrick(stats);
    }
    stats = BrickFall(stats);
    if (stats.inStats.timeType == 2)
    {
        stats = CollideWithWall(stats);
        stats = CollideWithRacket(stats);
        stats = CollideWithBrick(stats);
        stats = CheckDie(stats);
    }
    
	timer++;
    return stats;
}

void GamePhysics::Init()
{
    timer = 0;
    std::srand((unsigned int)time(NULL));
}