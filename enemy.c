
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprites.h"
#include "defs.h"
#include "enemy.h"

Enemy enemyInit(SDL_Renderer* renderer, SDL_Texture* sheet, SDL_Point* source, int score,int speed)
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
    enemy.score = score;
    enemy.base.state = ENTITY_ANIM1;
    enemy.base.speed = speed;
    return enemy;
}

void updateEnemies(Enemy* enemies, float deltaTime) 
{
    for (int i = 0; i < ENEMY_COUNT; i++) 
    {

        if (enemies[i].base.state != ENTITY_DEAD)
        {
            if (enemies[i].base.state == ENTITY_ANIM1 || enemies[i].base.state == ENTITY_ANIM2)
            {
                /*
            // 1. POHYB (letí dolů)
            enemy->base.y += ENEMY_SPEED * deltaTime;
            
            // Update pozice pro vykreslení
            enemy->base.sprite.destination.y = (int)enemy->base.y;
            enemy->base.sprite.destination.x = (int)enemy->base.x;
                */
            
            //ANIMACE
            enemies[i].base.animTimer += deltaTime;

            if (enemies[i].base.animTimer >= ANIMATION_SPEED) 
            {
                enemies[i].base.animTimer = 0.0f; // Reset časovače

                // Přepínání stavů
                if (enemies[i].base.state == ENTITY_ANIM1)
                {
                    enemies[i].base.state = ENTITY_ANIM2;
                    // Posun na druhý obrázek v textuře (offset o šířku)
                    enemies[i].base.sprite.source.x += enemies[i].base.sprite.source.w;
                } 
                else 
                {
                    enemies[i].base.state = ENTITY_ANIM1;
                   enemies[i].base.sprite.source.x -= enemies[i].base.sprite.source.w;
                }
            }
            /*
            // Ošetření vyletění z obrazovky
            if (enemy->base.y > WINDOW_HEIGHT) {
                enemy->active = false;
                enemy->base.state = ENTITY_DEAD;
            }*/
            }
        
        // --- VÝBUCH (EXPLODING) ---
            else if (enemies[i].base.state == ENTITY_EXPLODING)
            {
                enemies[i].base.animTimer += deltaTime;

                //zmena source na vybuch
                enemies[i].base.sprite.source.x = 3 * ENTITY_SIZE;
                enemies[i].base.sprite.source.y = 1 * ENTITY_SIZE;

                if (enemies[i].base.animTimer >= ANIMATION_SPEED) 
                {
                    enemies[i].base.state = ENTITY_DEAD;
                }
            }
        }
    }

       
}
