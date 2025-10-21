#include "Stats.h"

#pragma once
static class GameDisplay
{

    static void Draw(sf::RenderWindow& window, GameStats stats);

public:

    static void Update(sf::RenderWindow& window, GameStats stats);

};