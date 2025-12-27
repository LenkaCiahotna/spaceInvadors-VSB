
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
    player.lives = 3;
    player.base.state = ENTITY_ANIM1;
    return player;
}
