#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once

const float RACKET_SPEED = 16.0f;
const float RACKET_LENGTH = 100.0f;
const float RACKET_HEIGHT = 10.f;
const float PONG_RADIUS = 20.f;
const float INIT_POSY = 550.f;
const float INIT_SPEED = 1.f;
const int PHYSIC_FPF = 16;
const int SCREEN_LENGTH = 800;
const int SCREEN_HEIGHT = 600;
const float PI = 3.14159f;
const float ROTATE_SPEED = PI / 2.f / 30.f;
const float MAX_ROTATION = PI / 3.f;
const int BLOCK_LENGTH = 80;
const int BLOCK_HEIGHT = 60;
const float FALL_SPEED = 4.f;
const int RAND_PRECISION = 1000;
const int BRICK_ROWS = 4;
const int BRICK_COLUMNS = 8;
const float BRICK_LENGTH = SCREEN_LENGTH / BRICK_COLUMNS;
const float BRICK_HEIGHT = SCREEN_HEIGHT / BRICK_ROWS / 4.0;
const int TOP_OFFSET = 100;
const int WEAK_COLOR = 63;
const int STRONG_COLOR = 255;
const int NORMAL_BRICK_TYPE = 5;
const int PREDICT_STEP = 5;
const int PREDICT_DISTANCE = 60;
//const int ROTATE_SPEED = PI / 2.f / 30.f; ¾¯ÖÓ³¤Ãù

sf::Vector2f toRecCoord(float length, float direction);

float Distance(sf::Vector2f x, sf::Vector2f y);

float Hash(sf::Vector2f x);

sf::Vector2f Multiply(sf::Vector2f a, float b);