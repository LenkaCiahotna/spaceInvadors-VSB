#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "entity.h"

typedef struct {
    Entity base;
    int speed;       
    bool active;  
} Bullet;

Bullet bulletInit(SDL_Renderer* renderer, SDL_Texture* sheet, SDL_Rect source);
void updateBullets(Bullet *bullets, int count, double deltaTime);
