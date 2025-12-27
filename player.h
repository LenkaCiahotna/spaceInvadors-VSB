#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "entity.h"

typedef struct 
{
   Entity base;
   int lives;
}Player;

Player playerInit(SDL_Renderer* renderer, SDL_Texture* sheet);
