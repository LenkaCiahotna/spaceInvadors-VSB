#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"

Game gameInit(SDL_Renderer *renderer, SDL_Texture *sheet)
{
    Game game;
    memset(&game, 0, sizeof(Game));

    game.isRunning = true;
    game.player =  playerInit(renderer, sheet);
    SDL_Rect playerBulletrect = {
        .x = 13,
        .y = 2 * ENTITY_SIZE,
        .w = 5,
        .h = 20
    };

    for (int i = 0; i < MAX_PLAYER_BULLETS; i++) 
    {
        game.playerBullets[i] = bulletInit(renderer, sheet, playerBulletrect, -1);
    }   

    game.wave = 1;
    enemyHordeInit(renderer, sheet, &game.enemyHorde, game.wave);
       SDL_Rect enemyBulletrect = {
        .x = 0,
        .y = 2 * ENTITY_SIZE,
        .w = 13,
        .h = 20
    };
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++) 
    {
        game.enemyBullets[i] = bulletInit(renderer, sheet, enemyBulletrect, 1);
    } 
    return game;
}


GameContext gameContextInit(SDL_Renderer* renderer, SDL_Texture* sheet, TTF_Font* font)
{
    GameContext gameContext;
    memset(&gameContext, 0, sizeof(GameContext));

    gameContext.game = gameInit(renderer, sheet);

    char* labels[3] = {"Score", "00000", "Lives"};
    gameContext.itemCount = 3;

    for (int i = 0; i < gameContext.itemCount; i++) 
    {
        gameContext.items[i] = spriteInit(renderer, NULL, labels[i], font, NULL);
    }

    //SCORE
    gameContext.items[0].destination.x = 10;
    gameContext.items[0].destination.y = 10;

    //SCORE cisla
    gameContext.items[1].destination.x = 10 + gameContext.items[0].destination.w + 10 ;
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
    
    gameContext.lastRenderedScore = -1;

    return gameContext;
}



void handle_collisions_enemies(Game* game) 
{
    for (int i = 0; i < MAX_PLAYER_BULLETS; i++) 
    {
        if (game->playerBullets[i].active)
        {
            for (int y = 0; y < ENEMY_COUNT; y++)
            {
                if (game->enemyHorde.enemies[y].base.state != ENTITY_DEAD)
                {
                    if (SDL_HasIntersection(&game->playerBullets[i].base.sprite.destination, &game->enemyHorde.enemies[y].base.sprite.destination)) 
                    {
                        game->playerBullets[i].active = false;
                        game->enemyHorde.enemies[y].base.state = ENTITY_EXPLODING;
                        game->score +=  game->enemyHorde.enemies[y].score;
                        game->enemyHorde.aliveEnemies--;
                        printf("BUM!\n");
                        break; 
                    }
                }
            }
                
        }
    }
}

void handle_collisions_player(Game* game) 
{
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++) 
    {
        if (game->enemyBullets[i].active)
        {
            if (SDL_HasIntersection(&game->enemyBullets[i].base.sprite.destination, &game->player.base.sprite.destination)) 
            {
                game->enemyBullets[i].active = false;
                game->player.base.state = ENTITY_EXPLODING;
                game->player.lives--;
                printf("AU!\n");
                break; 
                    
            }
        }      
    }
}

void updateGame(GameContext* context,SDL_Renderer *renderer, TTF_Font* font, float deltaTime, SDL_Texture* sheet )
{
    bool invasionSuccess = false;
   
 
   
    handle_collisions_enemies(&context->game);
    handle_collisions_player(&context->game);
    updatePlayer(&context->game.player, deltaTime);
    if (context->game.player.base.state != ENTITY_EXPLODING)
    {
        invasionSuccess = updateEnemies(&context->game.enemyHorde, deltaTime);
        if (invasionSuccess ||  context->game.player.lives == 0)
        {
            printf("GAME OVER - Invasion Successful\n");
            context->game.player.lives = 0; 
        }
        enemyShoot(&context->game.enemyHorde, context->game.enemyBullets, deltaTime);
        updateBullets(context->game.playerBullets, MAX_PLAYER_BULLETS, deltaTime);
        updateBullets(context->game.enemyBullets, MAX_ENEMY_BULLETS, deltaTime);

        if (context->game.score != context->lastRenderedScore)
        {
            SDL_DestroyTexture(context->items[1].texture);
            char scoreText[10]; 
            sprintf(scoreText, "%05d", context->game.score);
            context->items[1] = spriteInit(renderer,NULL, scoreText, font, NULL);
            context->items[1].destination.x = 10 + context->items[0].destination.w + 10;
            context->items[1].destination.y = 10 ;
        }

        if (context->game.enemyHorde.aliveEnemies == 0)
        {
            context->game.wave++;
            resetBullets(context->game.playerBullets, MAX_PLAYER_BULLETS);
            enemyHordeInit(renderer, sheet, &context->game.enemyHorde, context->game.wave);
        }
   }
   


}


void renderGame(SDL_Renderer *renderer,GameContext* gameConx)
{
    //hrac
    drawSprite(renderer, &gameConx->game.player.base.sprite); //&((*sprite).source) == &sprite->source

    //hrac vystrely
    for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
    {
       if (gameConx->game.playerBullets[i].active)
       {
            drawSprite(renderer, &gameConx->game.playerBullets[i].base.sprite);
       }
       
    }
    
    //enemies
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        if (gameConx->game.enemyHorde.enemies[i].base.state != ENTITY_DEAD)
        {
           drawSprite(renderer, &gameConx->game.enemyHorde.enemies[i].base.sprite);
        }

    }

    //enemies vystrely
    for (int i = 0; i < MAX_ENEMY_BULLETS; i++)
    {
       if (gameConx->game.enemyBullets[i].active)
       {
            drawSprite(renderer, &gameConx->game.enemyBullets[i].base.sprite);
       }
       
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

void gameContextCleanup(GameContext* context)
{
    for (int i = 0; i < context->itemCount; i++) 
    {
        if (context->items[i].texture != NULL) 
        {
            SDL_DestroyTexture(context->items[i].texture);
            context->items[i].texture = NULL; 
        }
    }
}