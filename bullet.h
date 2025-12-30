#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "entity.h"

typedef struct {
    Entity base;   
    int speed;  
    bool active;  
    int direction; // 1 = nahoru, -1 dolu
} Bullet;

Bullet bulletInit(SDL_Renderer* renderer, SDL_Texture* sheet, SDL_Rect source, int direction);
void updateBullets(Bullet* bullets, int count, double deltaTime);
void resetBullets(Bullet* bullets, int count);