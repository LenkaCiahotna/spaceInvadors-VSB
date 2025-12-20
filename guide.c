#include <SDL2/SDL.h>
#include "guide.h"
#include "utils.h"
#include "sdl.h"

GuideContext guideInit(SDL_Renderer* renderer,  TTF_Font* font)
{
    GuideContext guide;
    char* labels[] = {
        "Guide",
        " ",
        "The Earth is under attack by alien invaders.",
        "You are the last pilot capable of stopping them.",
	    "Destroy enemies before they reach the ground.",
        "You have 3 lives.",
        " ", 
        "--- CONTROLS ---",
        "Move: Left / Right Arrows",
        "Shoot: Spacebar"
    };
    guide.itemsCount = 10;
    guide.font = font;
    int spacing = 30;
    int fontSize = 20;
    int totalHeight = ((guide.itemsCount - 1) * spacing) + fontSize;
    int startY = (WINDOW_HEIGHT - totalHeight) / 2;    

    makeTextSpriteArray(guide.items, renderer, labels, guide.itemsCount, guide.font, startY, 30);
    guide.backMessage = spriteInit(renderer, NULL, "press space to go back to menu", guide.font, NULL);
    guide.backMessage.destination.y = WINDOW_HEIGHT - spacing*2;
    guide.backMessage.destination.x = (WINDOW_WIDTH - guide.backMessage.destination.w ) / 2;
    return guide;
}

void guideRender(SDL_Renderer* renderer, GuideContext* guide)
{
    for(int i = 0; i < guide->itemsCount; i++) 
    {
        drawSprite(renderer, &guide->items[i]);
    }
    drawSprite(renderer, &guide->backMessage);
}

void guideCleanup(GuideContext* guide)
{
    for (int i = 0; i < guide->itemsCount; i++) {
        SDL_DestroyTexture(guide->items[i].texture);
    }
    TTF_CloseFont(guide->font);
}