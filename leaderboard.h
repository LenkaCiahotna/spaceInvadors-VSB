#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "sprites.h"

typedef struct{
    int finalScore;
    char playerName[MAX_NAME_LENGTH + 1]; // +1  pro \n
    int nameLength; 
}GameRecord;

typedef struct{
    Sprite headline;
    GameRecord records[10];
    Sprite rowSprites[10];
    int count;
    Sprite backMessage;
}LeaderboardContext;

LeaderboardContext leaderboardInit(SDL_Renderer* renderer, TTF_Font* font);
void renderLeaderboard(SDL_Renderer* renderer, LeaderboardContext* leaderboardContext);
void leaderboardCleanup(LeaderboardContext* leaderboard);
