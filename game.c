#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"

Game gameInit(SDL_Renderer *renderer, SDL_Texture *sheet)
{
    Game game;
    memset(&game, 0, sizeof(Game));

    game.player =  playerInit(renderer, sheet);
    SDL_Rect Bulletrect = {
        .x = 13,
        .y = 2 * ENTITY_SIZE,
        .w = 5,
        .h = 20
    };

    for (int i = 0; i < MAX_PLAYER_BULLETS; i++) 
    {
        game.playerBullets[i] = bulletInit(renderer, sheet, Bulletrect);
    }   
   
    game.isRunning = true;
    game.wave = 1;
    enemyHordeInit(renderer, sheet, &game.enemyHorde, game.wave);
    return game;
}


GameContext gameContextInit(SDL_Renderer* renderer, SDL_Texture* sheet, TTF_Font* font)
{
    GameContext gameContext;
    memset(&gameContext, 0, sizeof(GameContext));

    gameContext.game = gameInit(renderer, sheet);

    char* labels[3] = {"Score", "0000", "Lives"};
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

void playerShoot(Game *game)
{
    if (game->player.shootCooldown > 0) 
    {
        return; 
    }
    float playerCenter = game->player.base.posXf + (game->player.base.sprite.destination.w / 2.0f);
    float bulletHalf = game->playerBullets[0].base.sprite.destination.w / 2.0f;
            
    for (int i = 0; i < MAX_PLAYER_BULLETS; i++)
    {
        if (!game->playerBullets[i].active)
        {
            game->playerBullets[i].active = true;
            // centrovani strely na stred lodi
            game->playerBullets[i].base.posXf = playerCenter - bulletHalf;
            
            game->playerBullets[i].base.posYf = game->player.base.posYf;

            game->playerBullets[i].base.sprite.destination.x = (int)game->playerBullets[i].base.posXf;
            game->playerBullets[i].base.sprite.destination.y = (int)game->playerBullets[i].base.posYf;
            game->player.shootCooldown =  PLAYER_SHOOT_COOLDOWN;

            //strela nalezena, vyskocime z cyklu
            break; 
        }
    }
    printf("VYSTReEEEEL\n");
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

void updateGame(GameContext* context,SDL_Renderer *renderer, TTF_Font* font, float deltaTime, SDL_Texture* sheet )
{
   
    updatePlayer(&context->game.player, deltaTime);
    handle_collisions_enemies(&context->game);
    updateEnemies(&context->game.enemyHorde, deltaTime);
    updateBullets(context->game.playerBullets, MAX_PLAYER_BULLETS, deltaTime);
   

    if (context->game.score != context->lastRenderedScore)
    {
        SDL_DestroyTexture(context->items[1].texture);
        char scoreText[10]; 
        sprintf(scoreText, "%04d", context->game.score);
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