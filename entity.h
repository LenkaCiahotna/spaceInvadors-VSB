#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprites.h"
#include "defs.h"

typedef struct 
{
    Sprite sprite;
    float posXf; // skutecna pozice (des. cislo)
    float posYf;
    EntityState state;
    float animTimer;
    int speed;
}Entity;
