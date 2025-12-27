#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"

Game gameInit(SDL_Renderer *renderer, SDL_Texture *sheet)
{
    Game game;
    memset(&game, 0, sizeof(Game));

    game.player =  playerInit(renderer, sheet);
    game.enemyDirection = 1; // = zacinaji se hybat doprava
    game.isRunning = true;

    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        //mrizka 11 sloupcu 5 rad
        int col = i % ENEMY_COLS;
        int row = i / ENEMY_COLS;
        SDL_Point currentEnemySource = {0, 0}; 

        if (row == 0)
        {
            currentEnemySource.x = 0; 
        }
        else if (row == 1 || row == 2)
        {
            currentEnemySource.x = 2 * ENTITY_SIZE;
        }
        else
        {
            currentEnemySource.x = 4 * ENTITY_SIZE; 
        }
        game.enemies[i] = enemyInit(renderer, sheet, &currentEnemySource, 10, 10);

        game.enemies[i].base.sprite.destination.x = 20 + (col * (ENTITY_SIZE + 10));
        game.enemies[i].base.sprite.destination.y = 50 + (row * ENTITY_SIZE);
        game.enemies[i].base.speed = 10;
        game.enemies[i].score = (5 - row) * 10; //od 50 do 10
    }

    return game;
}

GameContext gameContextInit(SDL_Renderer *renderer, SDL_Texture *sheet, TTF_Font* font)
{
    GameContext gameContext;
    memset(&gameContext, 0, sizeof(GameContext));

    gameContext.game = gameInit(renderer, sheet);

    char* labels[3] = {"Score", "0", "Lives"};
    gameContext.itemCount = 3;

    for (int i = 0; i < gameContext.itemCount; i++) 
    {
        gameContext.items[i] = spriteInit(renderer, NULL, labels[i], font, NULL);
    }

    //SCORE
    gameContext.items[0].destination.x = 10;
    gameContext.items[0].destination.y = 10;

    //SCORE cisla
    gameContext.items[1].destination.x = 10 + gameContext.items[0].destination.w + gameContext.items[1].destination.w ;
    gameContext.items[1].destination.y = 10 ;

    //LIVES
    gameContext.items[2].destination.x = 10 ;
    gameContext.items[2].destination.y = WINDOW_HEIGHT - 10 - gameContext.items[2].destination.h;

    // LIVES sprites
    SDL_Rect rect = {
        .x = 1 * ENTITY_SIZE,
        .y = 1 * ENTITY_SIZE,
        .w = ENTITY_SIZE,
        .h = ENTITY_SIZE
    };

    for (int i = 0; i < gameContext.game.player.lives; i++)
    {
        gameContext.lifeIcons[i] = spriteInit(renderer, sheet, NULL,NULL, &rect);
        gameContext.lifeIcons[i].destination.x = gameContext.items[2].destination.w + 20 + i * gameContext.lifeIcons[i].destination.w; 
        gameContext.lifeIcons[i].destination.y =  WINDOW_HEIGHT - 10 -gameContext.items[2].destination.h;
    }
    

    return gameContext;
}

void renderGame(SDL_Renderer *renderer,GameContext* gameConx)
{
    //hrac
    drawSprite(renderer, &gameConx->game.player.base.sprite); //&((*sprite).source) == &sprite->source

    //enemies
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        drawSprite(renderer, &gameConx->game.enemies[i].base.sprite);
    }
    
    //texty
    for (int i = 0; i < gameConx->itemCount; i++)
    {
        drawSprite(renderer, &gameConx->items[i]);
    }

    //zivoty
    for (int i = 0; i < gameConx->game.player.lives; i++)
    {
         drawSprite(renderer, &gameConx->lifeIcons[i]);
    }
    
    

}