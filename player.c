
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprites.h"
#include "defs.h"
#include "player.h"

Player playerInit(SDL_Renderer* renderer, SDL_Texture* sheet)
{
    Player player;
    memset(&player, 0, sizeof(Player));

    SDL_Rect rect = {
        .x = 1 * ENTITY_SIZE,
        .y = 1 * ENTITY_SIZE,
        .w = ENTITY_SIZE,
        .h = ENTITY_SIZE
    };
    player.base.sprite = spriteInit(renderer, sheet, NULL,NULL, &rect);
    player.base.sprite.destination.x = WINDOW_WIDTH/2 + player.base.sprite.destination.w/2 ;
    player.base.sprite.destination.y = WINDOW_HEIGHT - 100;
    player.base.posXf =  player.base.sprite.destination.x;
    player.base.posYf =  player.base.sprite.destination.y;
    player.base.speed = 200;
    player.lives = 3;
    player.base.state = ENTITY_ANIM1;
    player.shootCooldown = 0.0f;
    player.animTimer = MAX_ANIMATION_DELAY;
    return player;
}

void updatePlayer(Player* player, double deltaTime) 
{
    const Uint8* state = SDL_GetKeyboardState(NULL); //dokud je klavesa dole, hrac se pohybuje
    
    // doleva
    if (state[SDL_SCANCODE_LEFT])
    {
        printf("DOLEVAAAA\n : %f", player->base.speed * deltaTime);
        player->base.posXf -= player->base.speed * deltaTime;
    }
    // doprava
    if (state[SDL_SCANCODE_RIGHT]) 
    {
        printf("DOPRAVAAAAA\n : %f", player->base.speed * deltaTime);
        player->base.posXf += player->base.speed * deltaTime;
    }

    //kontrola konce obrazovky
    if (player->base.posXf < 0) 
    {
        player->base.posXf = 0;
    }
    else if (player->base.posXf > WINDOW_WIDTH - player->base.sprite.destination.w) 
    {
        player->base.posXf = WINDOW_WIDTH - player->base.sprite.destination.w;
    }

    player->base.sprite.destination.x = (int)player->base.posXf;

    if (player->shootCooldown > 0)
    {
        player->shootCooldown -= deltaTime;
    }
}