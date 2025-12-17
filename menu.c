#include <SDL2/SDL.h>
#include "menu.h"
#include "utils.h"
#include "sdl.h"

void menuInit(MenuContext* menu, SDL_Renderer* renderer) {
    menu->selectedItem = 0;
    menu->itemCount = 4;
    
    // Načtení assetů
    menu->logoTexture = IMG_LoadTexture(renderer, "../assets/images/logo.png");
    menu->arrowTexture = IMG_LoadTexture(renderer, "../assets/images/arrow.png");
    menu->font = TTF_OpenFont("../assets/space_invaders.ttf", 20);

    char* labels[] = {"START GAME", "GUIDE", "LEADERBOARD", "QUIT"};
    int startY = 330;
    int spacing = 60;

    for (int i = 0; i < menu->itemCount; i++) {
        menu->items[i].texture = MakeTextTexture(labels[i], menu->font, renderer);
        
        int textW, textH;
        SDL_QueryTexture(menu->items[i].texture, NULL, NULL, &textW, &textH);
        
        menu->items[i].rect.x = (WINDOW_WIDTH - textW ) / 2;
        menu->items[i].rect.y = startY + (i * spacing);
        menu->items[i].rect.w = textW;
        menu->items[i].rect.h = textH;
    }
}

void menuRender(SDL_Context context, MenuContext* menu)
{
    int logoW = 250;
    int logoH = 200;
    SDL_Rect rect = {
        .x = (WINDOW_WIDTH - logoW) / 2, 
        .y = 50, 
        .w = logoW,
        .h = logoH
    };
    SDL_RenderCopy(context.renderer, menu->logoTexture, NULL, &rect);
    for (int i = 0; i < menu->itemCount; i++) 
    {
        SDL_RenderCopy(context.renderer, menu->items[i].texture, NULL, &menu->items[i].rect);
    }
    SDL_Rect targetRect = menu->items[menu->selectedItem].rect; 
    int rocketW = 30;
    int rocketH = 17;
    int padding = 20; 
    SDL_Rect rocketRect = {
                .x = targetRect.x - rocketW - padding,
                .y = targetRect.y + (targetRect.h - rocketH) / 2 - 5,
                .w = rocketW,
                .h = rocketH
                };
    SDL_RenderCopy(context.renderer, menu->arrowTexture, NULL, &rocketRect);
}

GameState menuHandleInput(MenuContext* menu, SDL_Event event)
{
    switch (event.key.keysym.sym) {
            case SDLK_UP:
                menu->selectedItem--;
                if (menu->selectedItem < 0) menu->selectedItem = menu->itemCount - 1;
                return STATE_MENU;
                break;
            case SDLK_DOWN:
                menu->selectedItem++;
                if (menu->selectedItem >= menu->itemCount) menu->selectedItem = 0;
                return STATE_MENU;
                break;
            case SDLK_RETURN: //ENTER   
            case SDLK_SPACE:
                if (menu->selectedItem == 0) return STATE_GAME;
                if (menu->selectedItem == 1) return STATE_GUIDE;
                if (menu->selectedItem == 2) return STATE_LEADERBOARD;
                if (menu->selectedItem == 3) return STATE_QUIT;
                break;
        }
}

void menuCleanup(MenuContext* menu)
{
    SDL_DestroyTexture(menu->logoTexture);
    SDL_DestroyTexture(menu->arrowTexture);
    for (int i = 0; i < menu->itemCount; i++) {
        SDL_DestroyTexture(menu->items[i].texture);
    }
    TTF_CloseFont(menu->font);
}