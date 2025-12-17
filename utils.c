#include "utils.h"

SDL_Texture* MakeTextTexture(char* text, TTF_Font* font, SDL_Renderer* renderer) 
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, (SDL_Color){255,255,255});
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture; 
}