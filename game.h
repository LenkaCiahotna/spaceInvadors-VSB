#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "leaderboard.h"

typedef struct 
{
    Player player;
    Bullet playerBullets[MAX_PLAYER_BULLETS];
    EnemyHorde enemyHorde;
    int wave;
    Bullet enemyBullets[MAX_ENEMY_BULLETS];
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

typedef struct 
{
    GameRecord record;
    Sprite items[6];
    int itemsCount;
} GameOverContext;

Game gameInit(SDL_Renderer *renderer, SDL_Texture *sheet);
GameContext gameContextInit(SDL_Renderer *renderer, SDL_Texture *sheet, TTF_Font* font);
void handle_collisions_enemies(Game* game);
void updateGame(GameContext* context,SDL_Renderer *renderer, TTF_Font* font, float deltaTime, SDL_Texture* sheet );
void gameContextCleanup(GameContext* context);
GameOverContext gameOverInit(SDL_Renderer* renderer, TTF_Font* font, int score);
void renderGameOver(SDL_Renderer *renderer, GameOverContext* over);
void updateNameTexture(GameOverContext* ctx, SDL_Renderer* renderer, TTF_Font* font);
void saveScore(char* name, int score);

void renderGame(SDL_Renderer *renderer,GameContext* gameConx);

