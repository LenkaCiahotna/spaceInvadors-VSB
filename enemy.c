
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprites.h"
#include "defs.h"
#include "enemy.h"

Enemy enemyInit(SDL_Renderer* renderer, SDL_Texture* sheet, SDL_Point* source)
{
    Enemy enemy;
    memset(&enemy, 0, sizeof(Enemy));

    SDL_Rect rect = {
        .x = source->x,
        .y = source->y,
        .w = ENTITY_SIZE,
        .h = ENTITY_SIZE
    };
    enemy.base.sprite = spriteInit(renderer, sheet, NULL,NULL, &rect);
    enemy.score = 0;
    enemy.base.state = ENTITY_ANIM1;
    enemy.base.speed = 0;
    enemy.base.animInterval = MAX_ANIMATION_DELAY;
    return enemy;
}

void updateEnemies(Enemy* enemies, int* direction, float deltaTime) 
{
    bool wallHit = false;
    for (int i = 0; i < ENEMY_COUNT; i++) 
    {
       
        if (enemies[i].base.state != ENTITY_DEAD)
        {
            if (enemies[i].base.state == ENTITY_ANIM1 || enemies[i].base.state == ENTITY_ANIM2)
            {
                
                // update vnitrnich souradnic 
                enemies[i].base.posXf += enemies[i].base.speed * deltaTime * (*direction) ;
                if (enemies[i].base.posXf + enemies[i].base.sprite.destination.w + 10 >= WINDOW_WIDTH
                    || enemies[i].base.posXf - 10 <= 0)
                {
                   wallHit = true;
                }
                
                if (wallHit)
                {
                    *direction *= -1;
                    wallHit = false;
                    for (int y = 0; y < ENEMY_COUNT; y++)
                    {
                        
                        enemies[y].base.posYf += 20.0f;
                        
                    }
                }
                              
                //ANIMACE
                enemies[i].base.animTimer += deltaTime;

                if (enemies[i].base.animTimer >= enemies[i].base.animInterval) 
                {
                    enemies[i].base.animTimer = 0.0f; 

                    if (enemies[i].base.state == ENTITY_ANIM1)
                    {
                        enemies[i].base.state = ENTITY_ANIM2;
                    
                        enemies[i].base.sprite.source.x += enemies[i].base.sprite.source.w;
                    } 
                    else 
                    {
                        enemies[i].base.state = ENTITY_ANIM1;
                        enemies[i].base.sprite.source.x -= enemies[i].base.sprite.source.w;
                    }
                    
                    // actual update pozice pro vykreslení
                    enemies[i].base.sprite.destination.x = (int)enemies[i].base.posXf;
                    enemies[i].base.sprite.destination.y = (int)enemies[i].base.posYf;
                }
                /*
                // Ošetření vyletění z obrazovky
                if (enemy->base.y > WINDOW_HEIGHT) {
                    enemy->active = false;
                    enemy->base.state = ENTITY_DEAD;
                }*/
                }
            
                //VYBUCH
            else if (enemies[i].base.state == ENTITY_EXPLODING)
            {
                enemies[i].base.animTimer += deltaTime;

                //zmena source na vybuch
                enemies[i].base.sprite.source.x = 3 * ENTITY_SIZE;
                enemies[i].base.sprite.source.y = 1 * ENTITY_SIZE;

                if (enemies[i].base.animTimer >=enemies[i].base.animInterval) 
                {
                    enemies[i].base.state = ENTITY_DEAD;
                }
            }


        }
    }

       
}
