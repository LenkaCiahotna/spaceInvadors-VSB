#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define ENTITY_SIZE 38
#define ENEMY_ROWS 5
#define ENEMY_COLS 11
#define ENEMY_COUNT (ENEMY_ROWS * ENEMY_COLS)
#define MAX_PLAYER_BULLETS 10
#define MAX_ENEMY_BULLETS 20
#define BULLET_HEIGHT 20
#define PLAYER_SHOOT_COOLDOWN 0.5f
#define PLAYER_Y (WINDOW_HEIGHT - 100)
#define MAX_ANIMATION_DELAY 0.8f
#define MIN_ANIMATION_DELAY 0.05f
#define ENEMY_STEP_X  10.0f 
#define ENEMY_DROP_Y  30.0f
#define MAX_SHOOT_DELAY 5.0f 
#define MIN_SHOOT_DELAY   0.2f
#define WAVE_BONUS   0.1f

typedef enum {
    STATE_MENU,   
    STATE_GAME,   
    STATE_PAUSE, 
    STATE_GUIDE,   
    STATE_LEADERBOARD,
    STATE_QUIT,
    STATE_GAMEOVER
} GameState;

typedef enum {
    ENTITY_ANIM1,
    ENTITY_ANIM2,
    ENTITY_EXPLODING,
    ENTITY_DEAD
} EntityState;