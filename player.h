#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "entity.h"
#include "bullet.h"

typedef struct 
{
   Entity base;
   int lives;
   float shootCooldown;
   float animTimer;
   float animInterval;
   int speed;
}Player;

Player playerInit(SDL_Renderer* renderer, SDL_Texture* sheet);
void playerShoot(Player* player, Bullet* bullets);
void updatePlayer(Player* player, double deltaTime);
