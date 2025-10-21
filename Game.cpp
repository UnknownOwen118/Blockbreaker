#include "Control.cpp"
#include "Physics.cpp"
#include "Display.cpp"
#include "Stats.cpp"

#ifndef GAME
#define GAME

class Game
{
    GameControl gameControl;
    GamePhysics gamePhysics;
    GameDisplay gameDisplay;
    GameStats gameStats;

public:
    void Init()
    {
        gameStats.Init();
    }

    void Update(sf::RenderWindow& window)
    {
        gameDisplay.Update(window, gameStats);
        gameStats = gamePhysics.Update(window, gameStats);
        gameStats = gameControl.Update(window, gameStats);
    }
};

#endif