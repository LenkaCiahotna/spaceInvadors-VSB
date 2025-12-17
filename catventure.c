#include <SDL2/SDL.h>

#include <time.h>
#include <stdlib.h>
#include "dynamic_array.h"
#include "sdl.h"
#include "utils.h"
#include "menu.h"

int main()
{
    srand((unsigned int)time(NULL));

    SDL_Context context = sdl_context_init("Space Invadors", WINDOW_WIDTH, WINDOW_HEIGHT);
    MenuContext menuContext;
    menuInit(&menuContext, context.renderer);
    GameState currentState = STATE_MENU;
    
    
    SDL_Event event;
    int running = 1;
    Uint64 last = SDL_GetPerformanceCounter();
    while (running == 1)
    {
        Uint64 now = SDL_GetPerformanceCounter();
        double deltaTime = (double)(now - last) / (double)((long long)SDL_GetPerformanceFrequency());

        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN) 
            {
                switch (currentState)
                {
                    case STATE_MENU:
                        currentState = menuHandleInput(&menuContext, event);
                            break;
                    default:
                    break;
                }
            }
        }

        //nabarvi pozadi
        SDL_SetRenderDrawColor(context.renderer, 0, 0, 0, 255);
        SDL_RenderClear(context.renderer);

        //vykresli dle statu
        switch (currentState)
        {
            case STATE_MENU:
               menuRender(context, &menuContext);
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
    menuCleanup(&menuContext);
    sdl_context_free(&context);
    return 0;
}
