#include <SDL2/SDL.h>
#include "menu.h"

MenuContext menuInit(SDL_Renderer* renderer, TTF_Font* font)
{
    MenuContext menu;
    menu.selectedItem = 0;
   
    SDL_Texture* logo = IMG_LoadTexture(renderer, "../assets/images/logo.png");
    menu.logo = spriteInit(renderer, logo, NULL, NULL, NULL);
    menu.logo.destination.x = WINDOW_WIDTH/2 - menu.logo.destination.w/2; 
    menu.logo.destination.y = 50;
    SDL_Texture* arrow = IMG_LoadTexture(renderer, "../assets/images/arrow.png");
    menu.arrow = spriteInit(renderer,arrow, NULL, NULL, NULL);

    char* labels[] = {"START GAME", "GUIDE", "LEADERBOARD", "QUIT"};
    menu.itemCount = 4;

    makeTextSpriteArray(menu.items, renderer, labels, menu.itemCount, font,330,60);
    return menu;
}

void menuRender(SDL_Renderer* renderer, MenuContext* menu)
{
    drawSprite(renderer, &menu->logo);
    for (int i = 0; i < menu->itemCount; i++) 
    {
        drawSprite(renderer, &menu->items[i]);
    }
    SDL_Rect targetRect = menu->items[menu->selectedItem].destination; 
    int padding = 20; 
    menu->arrow.destination.x =  targetRect.x -  menu->arrow.destination.w - padding;
    menu->arrow.destination.y =  targetRect.y + (targetRect.h -  menu->arrow.destination.h) / 2 - 5;
    drawSprite(renderer, &menu->arrow);
}

GameState menuHandleInput(MenuContext* menu, SDL_Event event)
{
    switch (event.key.keysym.sym) 
    {
            case SDLK_UP:
                menu->selectedItem--;
                if (menu->selectedItem < 0) menu->selectedItem = menu->itemCount - 1; 
                break;
            case SDLK_DOWN:
                menu->selectedItem++;
                if (menu->selectedItem >= menu->itemCount) menu->selectedItem = 0;
                break;
            case SDLK_RETURN: //ENTER   
            case SDLK_SPACE:
                if (menu->selectedItem == 0) return STATE_GAME;
                if (menu->selectedItem == 1) return STATE_GUIDE;
                if (menu->selectedItem == 2) return STATE_LEADERBOARD;
                if (menu->selectedItem == 3) return STATE_QUIT;
                break;
        }
    return STATE_MENU;
}

void menuCleanup(MenuContext* menu)
{
    SDL_DestroyTexture(menu->logo.texture);
    menu->logo.texture = NULL;
    SDL_DestroyTexture(menu->arrow.texture);
     menu->arrow.texture = NULL;
    for (int i = 0; i < menu->itemCount; i++) 
    {
        SDL_DestroyTexture(menu->items[i].texture);
        menu->items[i].texture = NULL;
    }

}