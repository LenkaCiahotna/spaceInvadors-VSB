
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprites.h"
#include "defs.h"
#include "player.h"
#include "bullet.h"

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
    player.base.sprite.destination.y = PLAYER_Y;
    player.base.posXf =  player.base.sprite.destination.x;
    player.base.posYf =  player.base.sprite.destination.y;
    player.speed = 200;
    player.lives = 3;
    player.base.state = ENTITY_ANIM1;
    player.shootCooldown = 0.0f;
    player.animTimer = 0;
    player.animInterval = MAX_ANIMATION_DELAY;
    return player;
}

void playerShoot(Player* player, Bullet* bullets)
{
        
    
    if (player->shootCooldown <= 0) 
    {
        float playerCenter = player->base.posXf + (player->base.sprite.destination.w / 2.0f);
        float bulletHalf = bullets[0].base.sprite.destination.w / 2.0f;
                
        for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
        {
            if (!bullets[i].active)
            {
                bullets[i].active = true;
                // centrovani strely na stred lodi
                bullets[i].base.posXf = playerCenter - bulletHalf;
                
                bullets[i].base.posYf = player->base.posYf;

                bullets[i].base.sprite.destination.x = (int)bullets[i].base.posXf;
                bullets[i].base.sprite.destination.y = (int)bullets[i].base.posYf;
                player->shootCooldown =  PLAYER_SHOOT_COOLDOWN;

                //strela nalezena, vyskocime z cyklu
                break; 
            }
        }
        printf("VYSTReEEEEL\n");
    }
    
}

void updatePlayer(Player* player, double deltaTime) 
{
    if(player->base.state != ENTITY_EXPLODING)
    {
         const Uint8* state = SDL_GetKeyboardState(NULL); //dokud je klavesa dole, hrac se pohybuje
    
        // doleva
        if (state[SDL_SCANCODE_LEFT])
        {
            player->base.posXf -= player->speed * deltaTime;
        }
        // doprava
        if (state[SDL_SCANCODE_RIGHT]) 
        {
            player->base.posXf += player->speed * deltaTime;
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
    //vybuch
    else if (player->base.state == ENTITY_EXPLODING)
    {
        if (player->animTimer == 0.0f)
        {
           //zmena source na vybuch
            player->base.sprite.source.x += player->base.sprite.source.w;
        }
        
        player->animTimer += deltaTime;
        printf("HRAC VYBUCHUJE\n");

        if (player->animTimer >= player->animInterval*2
             && player->lives > 0) 
        {
            player->animTimer = 0.0f;
            player->base.state = ENTITY_ANIM1;
            player->base.sprite.source.x -= player->base.sprite.source.w;
        }
    }
}