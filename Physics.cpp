#include "Physics.h"
#include "Stats.h"
#include <cmath>

int GamePhysics::timer = 0;

Brick GamePhysics::LimitRacket(Brick racket)
{
    if (racket.pos.x <= 0) racket.pos.x = 0;
    if (racket.pos.x + RACKET_LENGTH >= SCREEN_LENGTH)
        racket.pos.x = SCREEN_LENGTH - RACKET_LENGTH;
    return racket;
}
float GamePhysics::LimitDirection(float direction) {
    
    if (direction <= -MAX_ROTATION) direction = -MAX_ROTATION;
    if (direction >= MAX_ROTATION) direction = MAX_ROTATION;
	
    return direction;
}

Pong GamePhysics::LimitUnshotPong(Pong pong, Brick racket){
    pong.pos.x = racket.pos.x + RACKET_LENGTH / 2 - pong.radius;
    return pong;
}

Pong GamePhysics::CollideWithWall(Pong pong)
{
    if (pong.pos.x < 0)
    {
        pong.velocity.x = -pong.velocity.x;
        pong.pos.x = 0;
    }
    if (pong.pos.x > SCREEN_LENGTH - 2 * pong.radius)
    {
        pong.velocity.x = -pong.velocity.x;
        pong.pos.x = SCREEN_LENGTH - 2 * pong.radius;
    }
    if (pong.pos.y < 0)
    {
        pong.velocity.y = -pong.velocity.y;
        pong.pos.y = 0;
    }
    return pong;
}

Pong GamePhysics::PongMove(Pong pong)
{
    pong.pos += pong.velocity;
    return pong;
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

Pong GamePhysics::CollideWithRacket(Pong pong, Brick racket)
{
    float speed = std::sqrt(pong.velocity.x * pong.velocity.x + pong.velocity.y * pong.velocity.y);
    int flag = isCollideWithBrick(pong, racket);
    if (!flag) return pong;
    float dx = 2 * (pong.pos.x + pong.radius -
        racket.pos.x - racket.size.x / 2) / racket.size.x;
    pong.velocity = toRecCoord(speed, dx * MAX_ROTATION);
    if (flag == 2 || flag == 7 || flag == 8)
        pong.velocity.y = -pong.velocity.y;
    return pong;
}

Pong GamePhysics::CollideWithBrick(Pong pong, std::vector<Brick> bricks)
{
	float speed = std::sqrt(pong.velocity.x * pong.velocity.x + pong.velocity.y * pong.velocity.y);
    for (int i = 0; i < bricks.size(); i++)
    {
        int flag = isCollideWithBrick(pong, bricks[i]);
        if (!flag) continue;
        if (flag == 1 || flag == 2) 
            pong.velocity.y = -pong.velocity.y;
        else if (flag == 3 || flag == 4)
            pong.velocity.x = -pong.velocity.x;
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
			pong.velocity = toRecCoord(speed, direction);
		}
		pong = PongMove(pong);
    }
	return pong;
}

std::vector<Brick> GamePhysics::HitBrick(Pong pong, std::vector<Brick> bricks)
{
    for (int i = 0; i < bricks.size(); i++)
    {
        int flag = isCollideWithBrick(pong, bricks[i]);
        if (flag)
        {
            if (bricks[i].type == 1)
            {
                bricks.erase(bricks.begin() + i);
                i--;
            }
            else if (bricks[i].type == 2)
            {
                bricks[i].type = 1;
            }
        }
    }
    return bricks;
}

std::vector<Brick> GamePhysics::GenerateBrick(std::vector<Brick> bricks)
{
    Brick brick;
    brick.pos = { (rand() % (SCREEN_LENGTH - BLOCK_LENGTH)) * 1.0f, 0.0f};
    brick.size = { BLOCK_LENGTH, BLOCK_HEIGHT };
    brick.type = rand() % 3;
    bricks.push_back(brick);
    return bricks;
}

std::vector<Brick> GamePhysics::BrickFall(std::vector<Brick> bricks)
{
    for (int i = 0; i < bricks.size(); i++)
    {
        bricks[i].pos.y += FALL_SPEED;
        if (bricks[i].pos.y > SCREEN_HEIGHT)
        {
            bricks.erase(bricks.begin() + i);
            i--;
        }
    }
    return bricks;
}

bool GamePhysics::CheckDie(Pong pong)
{
    return pong.pos.y >= SCREEN_HEIGHT;
}

GameStats GamePhysics::Update(GameStats stats)
{
    if (!stats.isInGame) return stats;
    if (stats.inStats.timeType == 2)
    {
        stats.inStats.pong = PongMove(stats.inStats.pong);
    }
	//这里必须先移动球，再检测碰撞，否则发球时立刻碰撞会出问题
    stats.inStats.racket = LimitRacket(stats.inStats.racket);
	stats.inStats.direction = LimitDirection(stats.inStats.direction);
    if (stats.inStats.timeType == 1)
    {
		stats.inStats.pong = LimitUnshotPong(stats.inStats.pong, stats.inStats.racket);
    }
    if (timer % 20 == 0)
    {
        stats.inStats.bricks = GenerateBrick(stats.inStats.bricks);
    }
    stats.inStats.bricks = BrickFall(stats.inStats.bricks);
    if (stats.inStats.timeType == 2)
    {
        stats.inStats.pong = CollideWithWall(stats.inStats.pong);
        stats.inStats.pong = CollideWithRacket(stats.inStats.pong, stats.inStats.racket);
		std::vector<Brick> newBricks = HitBrick(stats.inStats.pong, stats.inStats.bricks);
        stats.inStats.pong = CollideWithBrick(stats.inStats.pong, stats.inStats.bricks);
		stats.inStats.bricks = newBricks;
        if (CheckDie(stats.inStats.pong))
            stats.Init();
    }
    
	timer++;
    return stats;
}

void GamePhysics::Init()
{
    timer = 0;
    std::srand((unsigned int)time(NULL));
}