#include <SFML/Graphics.hpp>

#ifndef ELEMENTS

#define ELEMENTS

class Brick
{
    public:
        sf::Vector2f pos;
        sf::Vector2f size;
        int type = 0;
    // 0 - unbreakable 1 - frail blocks 2 - solid blocks
};

class Pong
{
    public:
        sf::Vector2f pos;
        sf::Vector2f velocity;
        float radius;
};

#endif