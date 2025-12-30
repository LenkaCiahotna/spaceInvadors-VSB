#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.h"
#include "defs.h"
#include "bullet.h"

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
   float shootTimer;
   float shootInterval;
}EnemyHorde;


Enemy enemyInit(SDL_Renderer* renderer, SDL_Texture* sheet, SDL_Point* source);
bool updateEnemies(EnemyHorde* horde, float deltaTime) ;
void enemyShoot(EnemyHorde* horde, Bullet* bullets, float deltaTime);
void enemyHordeInit(SDL_Renderer* renderer, SDL_Texture* sheet, EnemyHorde* enemyHorde, int wave);
