#include <SDL2/SDL.h>
#include "menu.h"
#include "utils.h"
#include "bullet.h"

Bullet bulletInit(SDL_Renderer* renderer, SDL_Texture* sheet, SDL_Rect source)
{
    Bullet bullet;
    memset(&bullet, 0, sizeof(Bullet));

    bullet.base.sprite = spriteInit(renderer, sheet, NULL, NULL, &source);

    bullet.speed = 300;
    bullet.active = false;

    return bullet;
}

void updateBullets(Bullet *bullets, int count, double deltaTime)
{
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
        if (bullets[i].active)
        {
            bullets[i].base.posYf -= bullets[i].speed * deltaTime;

            bullets[i].base.sprite.destination.y = (int)bullets[i].base.posYf;

            // kontrola vyleteni z obrazovky
            if (bullets[i].base.posYf< -BULLET_HEIGHT || bullets[i].base.posYf > WINDOW_HEIGHT + BULLET_HEIGHT) 
            {
                bullets[i].active = false; 
            }
        }
    }
}