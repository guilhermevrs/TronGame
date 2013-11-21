#include "../includes/matrixcontroller.h"
#include <time.h>
#include <stdlib.h>

char globalMatrix[SCENE_HEIGHT][SCENE_WIDTH];

Player mainPlayer;
Player enemy1;
Player enemy2;

/*
    Checks if element is at the horizontal borders
    pos = Position of the element

    Returns: -1 = element is at the left border
                   1 = element is at the right border
                   0 = element is between the borders
*/
int isElementAtHorizontalBorder(Position pos)
{
    int retorno = 0;
    if(pos.x == SCENE_WIDTH - 1)
        retorno = 1;
    else if(pos.x == 0)
        retorno = -1;
    return retorno;
}

/*
    Checks if element is at the vertical borders
    pos = Position of the element

    Returns: -1 = element is at the up border
                   1 = element is at the bottom border
                   0 = element is between the borders
*/
int isElementAtVerticalBorder(Position pos)
{
    int retorno = 0;
    if(pos.y == SCENE_HEIGHT - 1)
        retorno = 1;
    else if(pos.y == 0)
        retorno = -1;
    return retorno;
}

/*
    Increments the position of a element
    *pos = pointer to the position that needs to be incremented
*/
void incrementElementPosition(Position *pos, char direction)
{
    switch(direction)
    {
        case DIRECTION_LEFT:
            if(isElementAtHorizontalBorder(*pos) >= 0)
                pos->x = pos->x - 1;
            else
                pos->x = SCENE_WIDTH -1;
        break;
        case DIRECTION_UP:
            if(isElementAtVerticalBorder(*pos) >= 0)
                pos->y = pos->y - 1;
            else
                pos->y = SCENE_HEIGHT -1;
        break;
        case DIRECTION_RIGHT:
            if(isElementAtHorizontalBorder(*pos) <= 0)
                pos->x = pos->x + 1;
            else
                pos->x = 0;
        break;
        case DIRECTION_DOWN:
        default:
            if(isElementAtVerticalBorder(*pos) <= 0)
                pos->y = pos->y + 1;
            else
                pos->y = 0;
        break;
    }
}

void initGameMatrix()
{
    int i, j;
    for (i = 0; i < SCENE_HEIGHT; ++i)
    {
        for (j = 0; j < SCENE_WIDTH; ++j)
        {
            globalMatrix[i][j] = GAME_SPACE;
        }
    }
    mainPlayer.position.x = 0;
    mainPlayer.position.y = 0;
	enemy1.position.x = 30;
	enemy1.position.y = 30;
	enemy2.position.x = 50;
	enemy2.position.y = 10;
    mainPlayer.direction = DIRECTION_RIGHT;
	enemy1.direction = DIRECTION_RIGHT;
	enemy2.direction = DIRECTION_RIGHT;    
	globalMatrix[0][0] = GAME_PLAYER;
	globalMatrix[30][30] = GAME_ENEMY;
	globalMatrix[50][10] = GAME_ENEMY;

    for (i = 12; i < 20; ++i)
    {
        for (j = 4; j < 6; ++j)
        {
            globalMatrix[i][j] = GAME_WALL;
        }

        for (j = 15; j < 20; ++j)
        {
            globalMatrix[i][j] = GAME_WALL;
        }
    }
}

/*
    Checks if happened a collision
*/
int isStepOk(Player thisPlayer)
{
    int matrixPosition = globalMatrix[thisPlayer.position.x][thisPlayer.position.y];
    int result;
    switch(matrixPosition)
    {
        case GAME_WALL:
            result = STEP_COLLISION_WALL;
        break;
        case GAME_ENEMY:
            result = STEP_COLLISION_ENEMY;
        break;
        case GAME_TRAIL:
            result = STEP_COLLISION_TRAIL;
        break;
        default:
            result = STEP_OK;
        break;
    }
    return result;
}

float randomFloat()
{
    srand(time(NULL));
    float r = (float)rand()/(float)RAND_MAX;
    return r;
}

void IAofEnemy(Player *enemy){
    int enemyStep = isStepOk(*enemy);
    float randomNumber;

    if((enemyStep==STEP_COLLISION_TRAIL) || (enemyStep==STEP_COLLISION_WALL))
    {
        switch(enemy->direction)
    {
        case DIRECTION_LEFT:{
                enemy->position.x = enemy->position.x + 1;
                    if(globalMatrix[enemy->position.x][enemy->position.y+1] == GAME_SPACE){
                        enemy->position.y = enemy->position.y + 1;
                        enemy->direction = DIRECTION_DOWN;
                    }
                    else
                        if(globalMatrix[enemy->position.x][enemy->position.y-1] == GAME_SPACE){
                             enemy->position.y = enemy->position.y - 1;
                            enemy->direction = DIRECTION_UP;
                        }
            }
        break;
        case DIRECTION_UP:{
                enemy->position.y = enemy->position.y + 1;
                if(globalMatrix[enemy->position.x+1][enemy->position.y] == GAME_SPACE){
                    enemy->position.x = enemy->position.x + 1;
                    enemy->direction = DIRECTION_RIGHT;
                }
                else
                    if(globalMatrix[enemy->position.x-1][enemy->position.y] == GAME_SPACE){
                         enemy->position.x = enemy->position.x - 1;
                         enemy->direction = DIRECTION_LEFT;
                    }
            }
        break;
        case DIRECTION_RIGHT:{
                enemy->position.x = enemy->position.x - 1;
                
                if((globalMatrix[enemy->position.x][enemy->position.y+1] == GAME_SPACE) && (globalMatrix[enemy->position.x][enemy->position.y+1] == GAME_SPACE))
                {
                    randomNumber = randomFloat();
                    printf("%f\n",randomNumber);
                }
                else
                if(globalMatrix[enemy->position.x][enemy->position.y+1] == GAME_SPACE){
                    enemy->position.y = enemy->position.y + 1;
                    enemy->direction = DIRECTION_DOWN;
                }
                else
                    if(globalMatrix[enemy->position.x][enemy->position.y-1] == GAME_SPACE){
                         enemy->position.y = enemy->position.y - 1;
                         enemy->direction = DIRECTION_UP;
                    }
            }
        break;
        case DIRECTION_DOWN:
        default:{
                enemy->position.y = enemy->position.y - 1;
                 if(globalMatrix[enemy->position.x+1][enemy->position.y] == GAME_SPACE){
                    enemy->position.x = enemy->position.x + 1;
                    enemy->direction = DIRECTION_RIGHT;
                }
                else
                    if(globalMatrix[enemy->position.x-1][enemy->position.y] == GAME_SPACE){
                         enemy->position.x = enemy->position.x - 1;
                         enemy->direction = DIRECTION_LEFT;
                    }
        break;
        }
    }
    }
}

/*
void translateMove(Player enemy)
{
    switch(enemy.direction)
    {
        case DIRECTION_LEFT:
        {

        }
        case DIRECTION_UP:
        {

        }
        case DIRECTION_RIGHT:
        {

        }
        case DIRECTION_DOWN:
        {

        }
    }
}
*/

int gameStep()
{

    int step, step_aux;

    globalMatrix[mainPlayer.position.x][mainPlayer.position.y] = GAME_TRAIL;
	globalMatrix[enemy1.position.x][enemy1.position.y] = GAME_TRAIL;
	globalMatrix[enemy2.position.x][enemy2.position.y] = GAME_TRAIL;
	
    incrementElementPosition( &(mainPlayer.position), mainPlayer.direction );
    incrementElementPosition( &(enemy1.position), enemy1.direction );
	incrementElementPosition( &(enemy2.position), enemy2.direction );

    step = isStepOk(mainPlayer);
    IAofEnemy(&enemy1);
    IAofEnemy(&enemy2);

    globalMatrix[mainPlayer.position.x][mainPlayer.position.y] = GAME_PLAYER;
	globalMatrix[enemy1.position.x][enemy1.position.y] = GAME_ENEMY;
	globalMatrix[enemy2.position.x][enemy2.position.y] = GAME_ENEMY;

    return step;
}
