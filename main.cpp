#include "Game.cpp"

Game game;

int main()
{
    sf::RenderWindow window(sf::VideoMode({ SCREEN_LENGTH, SCREEN_HEIGHT }), "Blockbreaker!");
    game.Init();
    while (window.isOpen())
    {
        game.Update(window);
    }

    return 0;
}