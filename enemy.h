#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.h"
#include "defs.h"

typedef struct 
{
   Entity base;
   int score;
}Enemy;

typedef struct 
{
   Enemy enemies[ENEMY_COUNT];
   int aliveEnemies;
   int enemyDirection; // 1 = doprava, -1 = doleva
   float enemyAnimTimer;
   float enemyAnimInterval;
}EnemyHorde;


Enemy enemyInit(SDL_Renderer* renderer, SDL_Texture* sheet, SDL_Point* source);
void updateEnemies(EnemyHorde* horde, float deltaTime);
void enemyHordeInit(SDL_Renderer* renderer, SDL_Texture* sheet, EnemyHorde* enemyHorde, int wave);
