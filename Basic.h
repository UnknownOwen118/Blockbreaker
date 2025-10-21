#include <SFML/Graphics.hpp>

#pragma once

const float RACKET_SPEED = 16.0f;
const float RACKET_LENGTH = 100.0f;
const float RACKET_HEIGHT = 10.f;
const float PONG_RADIUS = 20.f;
const float INIT_POSY = 550.f;
const float INIT_SPEED = 16.f;
const int SCREEN_LENGTH = 800;
const int SCREEN_HEIGHT = 600;
const float PI = 3.14159f;
const float ROTATE_SPEED = PI / 2.f / 30.f;
const float MAX_ROTATION = PI / 3.f;
//const int ROTATE_SPEED = PI / 2.f / 30.f; 

sf::Vector2f toRecCoord(float length, float direction);

float Distance(sf::Vector2f x, sf::Vector2f y);