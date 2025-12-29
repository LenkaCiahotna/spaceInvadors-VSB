#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

typedef struct 
{
    Player player;
    Bullet playerBullets[MAX_PLAYER_BULLETS];
    Enemy enemies[ENEMY_COUNT];
    Bullet enemyBullets[MAX_PLAYER_BULLETS];
    int enemyDirection; // 1 = doprava, -1 = doleva
    float enemyAnimTimer;
    float enemyAnimInterval;
    bool isRunning;
    int score;
}Game;

typedef struct 
{
    Game game;
    Sprite items[3];
    int lastRenderedScore;
    int itemCount;
    Sprite lifeIcons[3];
}GameContext;

Game gameInit(SDL_Renderer *renderer, SDL_Texture *sheet);
GameContext gameContextInit(SDL_Renderer *renderer, SDL_Texture *sheet, TTF_Font* font);
void playerShoot(Game *game);
void handle_collisions_enemies(Game* game);
void updateGame(GameContext* context,SDL_Renderer *renderer, TTF_Font* font);

void renderGame(SDL_Renderer *renderer,GameContext* gameConx);

