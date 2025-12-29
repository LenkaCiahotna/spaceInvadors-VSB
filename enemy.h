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

Enemy enemyInit(SDL_Renderer* renderer, SDL_Texture* sheet, SDL_Point* source);
void updateEnemies(Enemy* enemies, int* direction, float deltaTime);
