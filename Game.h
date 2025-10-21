#include "Control.h"
#include "Physics.h"
#include "Display.h"
#include "Stats.h"

#pragma once

class Game
{
    GameStats gameStats;

public:
    void Init();

    void Update(sf::RenderWindow& window);
};