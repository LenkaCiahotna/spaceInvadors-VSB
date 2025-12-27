#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "player.h"
#include "enemy.h"

typedef struct 
{
   Player player;
   Enemy enemies[ENEMY_COUNT];
   int enemyDirection; // 1 = doprava, -1 = doleva
   bool isRunning;
   int score;
}Game;

typedef struct 
{
    Game game;
    Sprite items[3];
    int itemCount;
    Sprite lifeIcons[3];
}GameContext;

Game gameInit(SDL_Renderer *renderer, SDL_Texture *sheet);
GameContext gameContextInit(SDL_Renderer *renderer, SDL_Texture *sheet, TTF_Font* font);
void renderGame(SDL_Renderer *renderer,GameContext* gameConx);
