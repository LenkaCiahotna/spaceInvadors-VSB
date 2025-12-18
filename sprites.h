#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

typedef struct{
    SDL_Texture* texture;
    SDL_Rect source; 
    SDL_Rect destination;
}Sprite;

Sprite spriteInit(SDL_Renderer* renderer, char* path, char* text, TTF_Font* font, SDL_Rect* source);
void drawSprite(SDL_Renderer* renderer, Sprite* sprite);