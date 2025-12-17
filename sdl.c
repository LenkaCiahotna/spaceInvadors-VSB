#include "sdl.h"

SDL_Context sdl_context_init(const char* window_name, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) && IMG_Init(IMG_INIT_PNG) && TTF_Init())
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG;
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
    {
        fprintf(stderr, "IMG_Init Error: %s\n", IMG_GetError());
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0)
    {
        fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }

    SDL_Window* window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }
    
    return (SDL_Context) {
        .window = window,
        .renderer = renderer
    };
}
void sdl_context_free(SDL_Context* ctx)
{
    SDL_DestroyRenderer(ctx->renderer);
    SDL_DestroyWindow(ctx->window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}