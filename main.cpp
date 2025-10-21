#include "Game.h"
#include <iostream>

Game game;

int main()
{
    std::cout << "Hello worrld!!!" << std::endl;
    sf::RenderWindow window(sf::VideoMode({ SCREEN_LENGTH, SCREEN_HEIGHT }), "Blockbreaker!");
    window.setFramerateLimit(30);
    game.Init();
    while (window.isOpen())
    {
        game.Update(window);
    }

    return 0;
}