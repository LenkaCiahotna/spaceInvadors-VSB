#include <SDL2/SDL.h>

#include <time.h>
#include <stdlib.h>
#include "sdl.h"
#include "menu.h"
#include "guide.h"
#include "game.h"

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
    MenuContext menuContext = menuInit(context.renderer, font);
    GuideContext guideContext = guideInit(context.renderer, font);

    GameContext gameContext;
    GameOverContext overContext;
    LeaderboardContext leaderBoardContext;
    GameState currentState = STATE_MENU;

    SDL_Event event;
    int running = 1;
    Uint64 last = SDL_GetPerformanceCounter();
    while (running == 1)
    {
        Uint64 now = SDL_GetPerformanceCounter();
        double deltaTime = (double)(now - last) / (double)((long long)SDL_GetPerformanceFrequency());
        // akce
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            switch (currentState)
            {
            case STATE_MENU:
                if (event.type == SDL_KEYDOWN)
                {
                    GameState nextState = menuHandleInput(&menuContext, event);
                    if (nextState == STATE_GAME)
                    {
                        gameContext = gameContextInit(context.renderer, spriteSheet, font);
                    }
                    currentState = nextState;
                }
                break;
            case STATE_GUIDE:
                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_SPACE)
                    {
                        currentState = STATE_MENU;
                    }
                }
                break;
            case STATE_GAME:
                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        currentState = STATE_MENU;
                    }
                    if (event.key.keysym.sym == SDLK_SPACE && gameContext.game.player.base.state != ENTITY_EXPLODING)
                    {
                        playerShoot(&gameContext.game.player, gameContext.game.playerBullets);
                    }
                }
                break;
            case STATE_GAMEOVER:
                // PRIDAVANI PISMEN
                if (event.type == SDL_TEXTINPUT)
                {
                    if (overContext.record.nameLength < MAX_NAME_LENGTH)
                    {
                        strcat(overContext.record.playerName, event.text.text);
                        overContext.record.nameLength++;

                        // UPDATE NAME TEXTURE
                        updateNameTexture(&overContext, context.renderer, font);
                    }
                }
               
                else if (event.type == SDL_KEYDOWN)
                {
                     // MAZANI PISMEN
                    if (event.key.keysym.sym == SDLK_BACKSPACE && overContext.record.nameLength > 0)
                    {
                        overContext.record.playerName[overContext.record.nameLength - 1] = '\0';
                        overContext.record.nameLength--;
                        updateNameTexture(&overContext, context.renderer, font);
                    }
                    // ULOZENI
                    else if (event.key.keysym.sym == SDLK_RETURN && strlen(overContext.record.playerName) != 0)
                    {
                        saveScore(overContext.record.playerName, overContext.record.finalScore);
                        SDL_StopTextInput();
                        currentState = STATE_MENU;
                    }
                }
                break;
            case STATE_LEADERBOARD:
                leaderBoardContext = leaderboardInit(context.renderer, font);
                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_SPACE)
                    {
                        currentState = STATE_MENU;
                    }
                }
                break;
            default:
                break;
            }
        }

        // update hry
        if (currentState == STATE_GAME)
        {
            // potrebuji plynuly pohyb
            updateGame(&gameContext, context.renderer, font, deltaTime, spriteSheet);
            if (gameContext.game.player.lives <= 0)
            {
                currentState = STATE_GAMEOVER;
                overContext = gameOverInit(context.renderer, font, gameContext.game.score);
                printf("VYTVORILA SE GAME OVER");
            }
        }

        // nabarvi pozadi
        SDL_SetRenderDrawColor(context.renderer, 0, 0, 0, 255);
        SDL_RenderClear(context.renderer);

        // vykresli dle statu
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
        case STATE_GAMEOVER:
            renderGameOver(context.renderer, &overContext);
            break;
        case STATE_LEADERBOARD:
            renderLeaderboard(context.renderer, &leaderBoardContext);
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

    // uklid
    menuCleanup(&menuContext);
    guideCleanup(&guideContext);
    gameContextCleanup(&gameContext);
    SDL_DestroyTexture(spriteSheet);
    TTF_CloseFont(font);
    sdl_context_free(&context);
    return 0;
}
