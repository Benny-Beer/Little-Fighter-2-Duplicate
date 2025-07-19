#pragma once
#include <SFML/Graphics.hpp>

// DIMENSIONS
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const float GRID_SIZE = 50.f;
const sf::Vector2f SCREEN_SIZE(SCREEN_WIDTH, SCREEN_HEIGHT);
const sf::FloatRect WORLD_BOUNDS(-25, 380, 1050, 420);
const sf::FloatRect SEARCHING_BOUNDS(50.f, 450.f, 900.f, 300.f);

// PHYSICS (SPEED, GRAVITY, ECT.)
const float ALLY_SPEED = 200.f;
const float BIG_WEAPON_THROWING_SPEED = 700.f;
const float BIG_WEAPON_GRAVITY = 1000.f;

// RANGES
const float ENEMY_ATTACK_RANGE = 60.f;

// TIMING PARAMS
const float KNOCKED_CHECK_DELAY = 1.5f;
const float WAVE_DELAY = 1.0f;
const float LEVEL_DELAY = 2.0f;

const float OBJECT_COLDOWN = 5.0f;
const float ATTACK_COLDOWN = 1.0f;

const float BLOCK_DURATION = 0.7f;
const float RETREAT_DURATION = 1.0f;
const float ATTACK_DURATION = 0.15f;

const float HIT_RECOVERY_TIME = 0.5f;
const float KNOCKED_RECOVERY_TIME = 1.5f;
const float OBJ_EXPLOTION_TIME = 0.65f;

