#include "Game.h"
#include "Control.h"
#include "Physics.h"
#include "Display.h"
#include "Stats.h"

void Game::Init()
{
    gameStats.Init();
}

void Game::Update(sf::RenderWindow& window)
{
    GameDisplay::Update(window, gameStats);
    gameStats = GamePhysics::Update(gameStats);
    gameStats = GameControl::Update(window, gameStats);
}