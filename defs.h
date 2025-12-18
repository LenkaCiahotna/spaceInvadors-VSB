#pragma once
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef enum {
    STATE_MENU,   
    STATE_GAME,   
    STATE_PAUSE, 
    STATE_GUIDE,   
    STATE_LEADERBOARD,
    STATE_QUIT,
    STATE_GAMEOVER
} GameState;