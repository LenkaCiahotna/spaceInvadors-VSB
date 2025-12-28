#include <SDL2/SDL.h>

#include <time.h>
#include <stdlib.h>
#include "dynamic_array.h"
#include "sdl.h"
#include "utils.h"
#include "menu.h"
#include "guide.h"
#include "player.h"
#include "enemy.h"
#include "game.h"
#include "bullet.h"

int main()
{
    srand((unsigned int)time(NULL));

    SDL_Context context = sdl_context_init("Space Invadors", WINDOW_WIDTH, WINDOW_HEIGHT);
    TTF_Font* font = TTF_OpenFont("../assets/space_invaders.ttf", 20);
    if (font == NULL) 
    {
        printf("CHYBA: Nepodarilo se nacist font!");
        return 1;
    }
    SDL_Texture* spriteSheet = IMG_LoadTexture(context.renderer, "../assets/spritesheet.png");
     if (spriteSheet == NULL) 
    {
        printf("CHYBA: Nepodarilo se nacist font!");
        return 1;
    }
    MenuContext menuContext =  menuInit(context.renderer, font);
    GuideContext guideContext = guideInit(context.renderer, font);
    
   
    GameContext gameContext;
    GameState currentState = STATE_MENU;

   
    SDL_Event event;
    int running = 1;
    Uint64 last = SDL_GetPerformanceCounter();
    while (running == 1)
    {
        Uint64 now = SDL_GetPerformanceCounter();
        double deltaTime = (double)(now - last) / (double)((long long)SDL_GetPerformanceFrequency());
        //akce
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN) 
            {
                //zamezeni drzeni klavesy
                /*if (event.key.repeat != 0)
                {
                   continue;
                }*/
                //zde M pro mute music?
                switch (currentState)
                {
                    case STATE_MENU:
                        GameState nextState = menuHandleInput(&menuContext, event);
                        if (nextState == STATE_GAME) 
                        {
                            gameContext = gameContextInit(context.renderer, spriteSheet, font);
                        }
                    currentState = nextState;
                    break;
                    case STATE_GUIDE:
                        if (event.key.keysym.sym == SDLK_SPACE)
                        {
                            currentState = STATE_MENU;
                        }   
                        break;
                    case STATE_GAME:
                        if (event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            currentState = STATE_MENU;
                        }
                        if (event.key.keysym.sym == SDLK_SPACE)
                        {
                            playerShoot(&gameContext.game);
                        }
                        break;
                    default:
                    break;
                }
            }
        }

        //update hry 
        if (currentState == STATE_GAME) 
        {
            // potrebuji plynuly pohyb
            updatePlayer(&gameContext.game.player, deltaTime);
            handle_collisions_enemies(&gameContext.game);
            updateEnemies(gameContext.game.enemies, deltaTime);
            updateBullets(gameContext.game.playerBullets, MAX_PLAYER_BULLETS, deltaTime);
            updateGame(&gameContext, context.renderer, font);
        }

        //nabarvi pozadi
        SDL_SetRenderDrawColor(context.renderer, 0, 0, 0, 255);
        SDL_RenderClear(context.renderer);

        //vykresli dle statu
        switch (currentState)
        {
            case STATE_MENU:
                menuRender(context.renderer, &menuContext);
            break;
            case STATE_GUIDE:
               guideRender(context.renderer, &guideContext);
                break;
            case STATE_GAME:
                renderGame(context.renderer, &gameContext);
                break;
            case STATE_QUIT:
                running = 0;
            break;
        
        default:
            break;
        }
       
        SDL_RenderPresent(context.renderer);
        last = now;
    }
    //uklid
    menuCleanup(&menuContext);
    guideCleanup(&guideContext);
    TTF_CloseFont(font);
    sdl_context_free(&context);
    return 0;
}
