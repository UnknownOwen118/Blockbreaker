#include "Basic.h"
#include <cmath>

float Distance(sf::Vector2f x, sf::Vector2f y)
{
    return std::sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y));
}

sf::Vector2f toRecCoord(float length, float direction)
{
    return { length * sin(direction), -length * cos(direction) };
}
// up is 0, right is +, left is -