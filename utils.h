#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Texture* MakeTextTexture(char* text, TTF_Font* font, SDL_Renderer* renderer);
