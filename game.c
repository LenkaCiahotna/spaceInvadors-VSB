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
        game.enemies[i] = enemyInit(renderer, sheet, &currentEnemySource);

        game.enemies[i].base.sprite.destination.x = 20 + (col * (ENTITY_SIZE + 10));
        game.enemies[i].base.sprite.destination.y = 50 + (row * ENTITY_SIZE);
        game.enemies[i].base.posXf = game.enemies[i].base.sprite.destination.x;
        game.enemies[i].base.posYf = game.enemies[i].base.sprite.destination.y;
        game.enemies[i].base.speed = 15;
        game.enemies[i].score = (5 - row) * 10; //od 50 do 10
    }
    game.enemyAnimTimer = MAX_ANIMATION_DELAY;
    game.enemyAnimInterval = MAX_ANIMATION_DELAY;

    return game;
}

GameContext gameContextInit(SDL_Renderer *renderer, SDL_Texture *sheet, TTF_Font* font)
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
                if (game->enemies[y].base.state != ENTITY_DEAD)
                {
                    if (SDL_HasIntersection(&game->playerBullets[i].base.sprite.destination, &game->enemies[y].base.sprite.destination)) 
                    {
                        game->playerBullets[i].active = false;
                        game->enemies[y].base.state = ENTITY_EXPLODING;
                        game->score +=  game->enemies[y].score;
                        printf("BUM!\n");
                        break; 
                    }
                }
            }
                
        }

    }
}

void updateGame(GameContext* context,SDL_Renderer *renderer, TTF_Font* font)
{
   if (context->game.score != context->lastRenderedScore)
    {
        SDL_DestroyTexture(context->items[1].texture);
        char scoreText[10]; 
        sprintf(scoreText, "%04d", context->game.score);
        context->items[1] = spriteInit(renderer,NULL, scoreText, font, NULL);
        context->items[1].destination.x = 10 + context->items[0].destination.w + 10;
        context->items[1].destination.y = 10 ;
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
        if (gameConx->game.enemies[i].base.state != ENTITY_DEAD)
        {
           drawSprite(renderer, &gameConx->game.enemies[i].base.sprite);
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