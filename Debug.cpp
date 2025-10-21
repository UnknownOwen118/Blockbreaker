#include "Debug.h"
#include <iostream>

void GameDebug::Log(GameStats stats)
{
	std::cout << "Direction: " << stats.inStats.direction << std::endl;
	std::cout << "Pong Velocity: (" << stats.inStats.pong.velocity.x << ", " << stats.inStats.pong.velocity.y << ")" << std::endl;
}