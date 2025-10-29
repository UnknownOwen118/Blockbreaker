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

float Hash(sf::Vector2f x)
{
    int k1 = x.x * 1437;
    int k2 = x.y * 1919;
    int k = k1 ^ k2;
    k = (k * 1000000007 + 114514) % 19260817;
    return (k % RAND_PRECISION) / (1.0 * RAND_PRECISION);
}

sf::Vector2f Multiply(sf::Vector2f a, float b)
{
    return { a.x * b, a.y * b };
}