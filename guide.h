#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "defs.h"
#include "sdl.h"
#include "sprites.h"

typedef struct {
    Sprite items[10]; 
    TTF_Font* font;
    int itemsCount;  
    Sprite backMessage;
} GuideContext;

GuideContext guideInit(SDL_Renderer* renderer,  TTF_Font* font);
void guideRender(SDL_Renderer* renderer, GuideContext* guide);
void guideCleanup(GuideContext* guide);