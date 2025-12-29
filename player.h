#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "entity.h"

typedef struct 
{
   Entity base;
   int lives;
   float shootCooldown;
   float animTimer;
   int speed;
}Player;

Player playerInit(SDL_Renderer* renderer, SDL_Texture* sheet);
void updatePlayer(Player* player, double deltaTime);
