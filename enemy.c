
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprites.h"
#include "defs.h"
#include "enemy.h"


Enemy enemyInit(SDL_Renderer* renderer, SDL_Texture* sheet, SDL_Point* source)
{
    Enemy enemy;
    memset(&enemy, 0, sizeof(Enemy));

    SDL_Rect rect = {
        .x = source->x,
        .y = source->y,
        .w = ENTITY_SIZE,
        .h = ENTITY_SIZE
    };
    enemy.base.sprite = spriteInit(renderer, sheet, NULL,NULL, &rect);
    enemy.score = 0;
    enemy.base.state = ENTITY_ANIM1;
    return enemy;
}

void enemyHordeInit(SDL_Renderer* renderer, SDL_Texture* sheet, EnemyHorde* enemyHorde, int wave)
{
    enemyHorde->enemyDirection = 1; // = zacinaji se hybat doprava
    enemyHorde->aliveEnemies = ENEMY_COUNT;
    float waveBonus = (float)(wave - 1) * WAVE_BONUS; 
    enemyHorde->enemyAnimInterval = MAX_ANIMATION_DELAY - waveBonus;
    if (enemyHorde->enemyAnimInterval < MIN_ANIMATION_DELAY)
    {
        enemyHorde->enemyAnimInterval = MIN_ANIMATION_DELAY; 
    } 
    enemyHorde->shootInterval = MAX_SHOOT_DELAY - waveBonus;
    if (enemyHorde->shootInterval < MIN_SHOOT_DELAY)
    {
        enemyHorde->shootInterval = MIN_SHOOT_DELAY;
    }
    enemyHorde->enemyAnimTimer = enemyHorde->enemyAnimInterval;
   
    enemyHorde->shootTimer = 0.0f;
   

    float startY = 50.0f + ((wave - 1) * ENEMY_DROP_Y);
    
    if (startY > WINDOW_HEIGHT/2)
    {
        startY = WINDOW_HEIGHT/2;
    }
     
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
        enemyHorde->enemies[i] = enemyInit(renderer, sheet, &currentEnemySource);

        enemyHorde->enemies[i].base.sprite.destination.x = 20 + (col * (ENTITY_SIZE + 10));
        enemyHorde->enemies[i].base.sprite.destination.y = startY + (row * ENTITY_SIZE);
        enemyHorde->enemies[i].base.posXf = enemyHorde->enemies[i].base.sprite.destination.x;
        enemyHorde->enemies[i].base.posYf = enemyHorde->enemies[i].base.sprite.destination.y;
        enemyHorde->enemies[i].score = (5 - row) * 10; //od 50 do 10
    }
   

}

void enemyShoot(EnemyHorde* horde, Bullet* bullets, float deltaTime)
{
    horde->shootTimer += deltaTime;
    if (horde->shootTimer >= horde->shootInterval)
    {
        horde->shootTimer = 0.0f; 

        //hledam vzdy nejspodnejsiho enemy v kazdem sloupci
        int shooters[ENEMY_COLS]; 
        int shootersCount = 0;

        for (int col = 0; col < ENEMY_COLS; col++)
        {
            // odspodu nahoru
            for (int row = ENEMY_ROWS - 1; row >= 0; row--)
            {
                int index = row * ENEMY_COLS + col;

                if (horde->enemies[index].base.state != ENTITY_DEAD && 
                    horde->enemies[index].base.state != ENTITY_EXPLODING)
                {
                    //nasla jsem nejspodnejsiho -> pridam ho do vyberu
                    shooters[shootersCount] = index;
                    shootersCount++;
                    break; 
                }
            }
        }

        // VYSTRELENI
        if (shootersCount > 0)
        {
            int randomShooterIndex = shooters[rand() % shootersCount];
            Enemy* shooter = &horde->enemies[randomShooterIndex];
            printf("STRILI ENEMY %d\n", randomShooterIndex);
            // najdeme volnou strelu
            for (int i = 0; i < MAX_PLAYER_BULLETS; i++) 
            {
                if (!bullets[i].active)
                {
                    printf("nasla se strela\n");
                    bullets[i].active = true;
                    
                    // vycentrovani strely
                    bullets[i].base.posXf = shooter->base.posXf + (ENTITY_SIZE / 2) - bullets[i].base.sprite.destination.w/2; 
                    bullets[i].base.posYf = shooter->base.posYf + ENTITY_SIZE; 
                    
                    bullets[i].base.sprite.destination.x = (int)bullets[i].base.posXf;
                    bullets[i].base.sprite.destination.y = (int)bullets[i].base.posYf;
                    break; 
                }
            }
        }
    }
    
}

bool updateEnemies(EnemyHorde* horde, float deltaTime) 
{
    bool wallHit = false;
    bool invaded = false;
    horde->enemyAnimTimer += deltaTime;

    //vypocet zrychleni - dle poctu zbyvajcich ememies
    float aliveRatio = (float)horde->aliveEnemies / (float)ENEMY_COUNT;
    horde->enemyAnimInterval = MIN_ANIMATION_DELAY + (aliveRatio * (MAX_ANIMATION_DELAY - MIN_ANIMATION_DELAY));
    //pro jistotu - nemelo by nastat nikdy
    if (horde->enemyAnimInterval < MIN_ANIMATION_DELAY)
    {
        horde->enemyAnimInterval = MIN_ANIMATION_DELAY;
    } 

    //VYBUCH - prvni bo chceme okamzitou reakci
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        if (horde->enemies[i].base.state == ENTITY_EXPLODING)
        {
            horde->enemyAnimTimer += deltaTime;

            //zmena source na vybuch
            horde->enemies[i].base.sprite.source.x = 3 * ENTITY_SIZE;
            horde->enemies[i].base.sprite.source.y = 1 * ENTITY_SIZE;

            if (horde->enemyAnimTimer >=horde->enemyAnimInterval) 
            {
                horde->enemies[i].base.state = ENTITY_DEAD;
            }
        }

        if (horde->enemies[i].base.posYf + ENTITY_SIZE >= PLAYER_Y)
        {
           invaded = true;
        }
    }

    // pak casovana animace
    if (horde->enemyAnimTimer >= horde->enemyAnimInterval) 
    {
        horde->enemyAnimTimer  = 0.0f;
        for (int i = 0; i < ENEMY_COUNT; i++) 
        {
        
            if (horde->enemies[i].base.state != ENTITY_DEAD)
            {
                if (horde->enemies[i].base.state == ENTITY_ANIM1 || horde->enemies[i].base.state == ENTITY_ANIM2)
                {
                    
                    // update vnitrnich souradnic 
                    horde->enemies[i].base.posXf += ENEMY_STEP_X * horde->enemyDirection;
                    if (horde->enemies[i].base.posXf + horde->enemies[i].base.sprite.destination.w + 10 >= WINDOW_WIDTH
                        ||horde->enemies[i].base.posXf - 10 <= 0)
                    {
                        wallHit = true;
                    }  

                    // actual update pozice pro vykreslení
                    horde->enemies[i].base.sprite.destination.x = (int)horde->enemies[i].base.posXf;
                    horde->enemies[i].base.sprite.destination.y = (int)horde->enemies[i].base.posYf;

                    //animace
                    if (horde->enemies[i].base.state == ENTITY_ANIM1)
                    {
                        horde->enemies[i].base.state = ENTITY_ANIM2;   
                        horde->enemies[i].base.sprite.source.x += horde->enemies[i].base.sprite.source.w;
                    } 
                    else 
                    {
                        horde->enemies[i].base.state = ENTITY_ANIM1;
                        horde->enemies[i].base.sprite.source.x -= horde->enemies[i].base.sprite.source.w;
                    }
                
                }
                

            }
        
        }

        if (wallHit)
        {
            horde->enemyDirection *= -1;
            wallHit = false;
            for (int y = 0; y < ENEMY_COUNT; y++)
            {
                horde->enemies[y].base.posXf += ENEMY_STEP_X * horde->enemyDirection;
                horde->enemies[y].base.posYf += ENEMY_DROP_Y;       
                horde->enemies[y].base.sprite.destination.x = (int)horde->enemies[y].base.posXf;
                horde->enemies[y].base.sprite.destination.y = (int)horde->enemies[y].base.posYf;               
            }
        }
 
    }
    return invaded;
        
}
