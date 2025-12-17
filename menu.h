#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "defs.h"
#include "sdl.h"

typedef struct{
    SDL_Texture* texture;
    SDL_Rect rect; 
} MenuItem;

typedef struct {
    SDL_Texture* logoTexture;
    SDL_Texture* arrowTexture;
    TTF_Font* font;
    MenuItem items[4];
    int itemCount;
    int selectedItem;
} MenuContext;

void menuInit(MenuContext* menu, SDL_Renderer* renderer);
GameState menuHandleInput(MenuContext* menu, SDL_Event event);
void menuRender(SDL_Context context, MenuContext* menu);
void menuCleanup(MenuContext* menu);