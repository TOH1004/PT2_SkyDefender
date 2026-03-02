#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <winbgim.h>

// Game constants
const int WIDTH = 800;
const int HEIGHT = 600;
const int PLAYER_SPEED = 9;
const int BULLET_SPEED = 10;
const int ENEMY_SPEED = 3;
const int ENEMY_SPAWN_RATE = 30;
const COLORREF PLAYER_COLOR = COLOR(0, 0, 255); //blue
const COLORREF ENEMY_COLOR = COLOR(255, 0, 0); //red
const COLORREF PLAYER_BULLET_COLOR = COLOR(255, 255, 255); //white
const COLORREF ENEMY_BULLET_COLOR = COLOR(255, 255, 0); //yellow

// Array size limits
const int MAX_PLAYER_BULLETS = 100;
const int MAX_ENEMY_BULLETS = 200;
const int MAX_ENEMIES = 50;

#endif