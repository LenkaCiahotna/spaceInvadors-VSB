#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define ENTITY_SIZE 38
#define ENEMY_ROWS 5
#define ENEMY_COLS 11
#define ENEMY_COUNT (ENEMY_ROWS * ENEMY_COLS)

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