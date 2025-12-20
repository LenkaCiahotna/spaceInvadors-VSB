#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "defs.h"
#include "sdl.h"
#include "sprites.h"

typedef struct {
    Sprite logo;
    Sprite arrow;
    Sprite items[4];
    TTF_Font* font;
    int itemCount;
    int selectedItem;
} MenuContext;

MenuContext menuInit(SDL_Renderer* renderer, TTF_Font* font);
GameState menuHandleInput(MenuContext* menu, SDL_Event event);
void menuRender(SDL_Renderer* renderer, MenuContext* menu);
void menuCleanup(MenuContext* menu);