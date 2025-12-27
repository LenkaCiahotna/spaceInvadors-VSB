
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
    enemy.speed = speed;
    return enemy;
}
