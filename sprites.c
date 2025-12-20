#include <SDL2/SDL.h>
#include "menu.h"
#include "utils.h"
#include "sdl.h"
#include "sprites.h"

Sprite spriteInit(SDL_Renderer* renderer, char* path, char* text, TTF_Font* font, SDL_Rect* source)
{
    Sprite s = {NULL, {0,0,0,0}, {0,0,0,0}};
    if(text != NULL && font != NULL)
    {
        SDL_Surface* surface = TTF_RenderText_Solid(font, text, (SDL_Color){255,255,255,255});
        s.texture = SDL_CreateTextureFromSurface(renderer, surface);
        s.source = (SDL_Rect){0, 0, surface->w, surface->h};
        s.destination = (SDL_Rect){0, 0, surface->w, surface->h};
        SDL_FreeSurface(surface);
    }
    else if (path != NULL)
    {
        s.texture = IMG_LoadTexture(renderer, path);
        int w, h;
        SDL_QueryTexture(s.texture, NULL, NULL, &w, &h);
        
        if (source != NULL) 
        {
            s.source = *source; // vyrez ze sheetu
        }
        else 
        {
            s.source = (SDL_Rect){0, 0, w, h}; // cely obrazek, abych mohla dat do destination
        }
        s.destination = (SDL_Rect){0, 0, s.source.w, s.source.h};
    }
    
      return s; 
}

void drawSprite(SDL_Renderer* renderer, Sprite* sprite)
{
    //&((*sprite).source) == &sprite->source
    SDL_RenderCopy(renderer, sprite->texture, &sprite->source, &sprite->destination);
}

void makeTextSpriteArray(Sprite* items, SDL_Renderer* renderer, char* labels[], int itemCount, TTF_Font* font, int startY, int spacing)
{
    for (int i = 0; i < itemCount; i++) 
    {
        items[i] = spriteInit(renderer, NULL, labels[i], font, NULL);
        
        items[i].destination.x = (WINDOW_WIDTH - items[i].destination.w ) / 2;
        items[i].destination.y = startY + (i * spacing);
    }
}