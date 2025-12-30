#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include "leaderboard.h"

LeaderboardContext leaderboardInit(SDL_Renderer* renderer, TTF_Font* font)
{
    LeaderboardContext leaderboardContext;
    memset(&leaderboardContext, 0, sizeof(LeaderboardContext));

    // NADPIS
    leaderboardContext.headline = spriteInit(renderer, NULL, "TOP 10 PLAYERS", font, NULL);
    leaderboardContext.headline.destination.x = WINDOW_WIDTH / 2 - leaderboardContext.headline.destination.w / 2;
    leaderboardContext.headline.destination.y = 50;

    //BACK MESSAGE
    leaderboardContext.backMessage = spriteInit(renderer, NULL, "press space to go back to menu", font, NULL);
    leaderboardContext.backMessage.destination.y = WINDOW_HEIGHT - SPACING*2;
    leaderboardContext.backMessage.destination.x = (WINDOW_WIDTH - leaderboardContext.backMessage.destination.w ) / 2;

    //OTEVRENI SOUBORU
    FILE* file = fopen("leaderboard.csv", "r");
    if (file == NULL)
    {
        return leaderboardContext; 
    } 

    char line[128];
    leaderboardContext.count = 0; 

    // CTENI SOUBORU
    while (fgets(line, sizeof(line), file))
    {
        // odstraneni noveho radku
        // strcspn(radek, znak) -> vrati index na kterem ten znak je
        line[strcspn(line, "\n")] = 0;

        char nameBuf[50];
        int scoreBuf;

        // nacteni dat ze radku, cte dokud nenarazi na carku
        if (sscanf(line, "%[^,],%d", nameBuf, &scoreBuf) == 2)
        {
            int insertAt = -1; 

            for (int i = 0; i < 10; i++)
            {          
                //pokud nemame jeste 10 zaznamu tak ho priradime      
                if (i >= leaderboardContext.count) 
                {
                    insertAt = i;
                    break;
                }
                
                // pokud uz mame 10 a skore prochazeneho radku je vetsi nez i-ty radek tak ho prepisem
                if (scoreBuf > leaderboardContext.records[i].finalScore) 
                {
                    insertAt = i;
                    break;
                }
            }

            // vlozime nas radek na index
            if (insertAt != -1)
            {
                //top 10 list posuneme, aby bylo misto na novy radek
                for (int j = 9; j > insertAt; j--)
                {
                    leaderboardContext.records[j] = leaderboardContext.records[j - 1];
                }

                //vlozime
                strcpy(leaderboardContext.records[insertAt].playerName, nameBuf);
                leaderboardContext.records[insertAt].finalScore = scoreBuf;

                // zvysime kolik mame (pokud uz nemame 10)
                if (leaderboardContext.count < 10)
                {
                    leaderboardContext.count++;
                } 
            }
        }
    }
    fclose(file);

    // TEXTURY
    leaderboardContext.count = leaderboardContext.count;
    for (int i = 0; i < leaderboardContext.count; i++)
    {
        //vytvorime si 1 radek zaznamu
        char buffer[64];
        sprintf(buffer, "%d. %s ..... %d", i + 1, leaderboardContext.records[i].playerName, leaderboardContext.records[i].finalScore);
        
        leaderboardContext.rowSprites[i] = spriteInit(renderer, NULL, buffer, font, NULL);
        
        leaderboardContext.rowSprites[i].destination.x = WINDOW_WIDTH / 2 - leaderboardContext.rowSprites[i].destination.w / 2;
        leaderboardContext.rowSprites[i].destination.y = 150 + (i * SPACING);
    }

    return leaderboardContext;
}

void renderLeaderboard(SDL_Renderer* renderer, LeaderboardContext* leaderboardContext)
{
    drawSprite(renderer, &leaderboardContext->headline);

    for (int i = 0; i < leaderboardContext->count; i++)
    {
        if (leaderboardContext->rowSprites[i].texture != NULL) 
        {
            drawSprite(renderer, &leaderboardContext->rowSprites[i]);
        }
    }

    drawSprite(renderer, &leaderboardContext->backMessage);
}