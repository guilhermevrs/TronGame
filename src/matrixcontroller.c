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
            if(isElementAtVerticalBorder(*pos) <= 0){
                pos->y = pos->y + 1;
            }
            else
                pos->y = 0;
        break;
    }
}

void decrementElementPosition(Position *pos, char direction)
{
    switch(direction)
    {
        case DIRECTION_LEFT:
            if(isElementAtHorizontalBorder(*pos) > 0)
                pos->x = 0;
            else
                pos->x = pos->x + 1;
        break;
        case DIRECTION_UP:
            if(isElementAtVerticalBorder(*pos) > 0)
                pos->y = 0;
            else
                pos->y = pos->y + 1;
        break;
        case DIRECTION_RIGHT:
            if(isElementAtHorizontalBorder(*pos) > 0)
                pos->x = SCENE_WIDTH -1;
            else
                pos->x = pos->x - 1;
        break;
        case DIRECTION_DOWN:
        default:
            if(isElementAtVerticalBorder(*pos) < 0)
                pos->y = SCENE_HEIGHT-1;
            else
                pos->y = pos->y -1;
        break;
    }
}

void initGameMatrix(char* nomeArquivo)
{

    FILE * file = fopen(nomeArquivo, "r");
    char pixelzinho;
    int i=0, j=0;
    if( file == NULL ){
        printf("Impossible to open the file !\n");
        exit(0);
    }


    while(!feof(file))
    {
        pixelzinho = getc(file);
        if(pixelzinho != '\n'){
            if(pixelzinho != '1')
                globalMatrix[i][j] = GAME_SPACE;
            else
                globalMatrix[i][j] = GAME_WALL;
            j++;
        }
        else
        {
            j=0;
            i++;
        }
    }

    fclose(file);

    mainPlayer.position.x = 1;
    mainPlayer.position.y = 0;
    enemy1.position.x = 20;
    enemy1.position.y = 20;
    enemy2.position.x = 40;
    enemy2.position.y = 0;
    mainPlayer.direction = DIRECTION_RIGHT;
    enemy1.direction = DIRECTION_RIGHT;
    enemy2.direction = DIRECTION_DOWN;
    mainPlayer.state = PLAYER_ALIVE;
    enemy1.state = PLAYER_ALIVE;
    enemy2.state = PLAYER_ALIVE;
    globalMatrix[1][0] = GAME_PLAYER;
    globalMatrix[20][20] = GAME_ENEMY_1;
    globalMatrix[40][0] = GAME_ENEMY_2;
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
            result = STEP_COLLISION;
        break;
        case GAME_ENEMY_1:
            result = STEP_COLLISION;
        break;
        case GAME_ENEMY_2:
            result = STEP_COLLISION;
        break;

        case GAME_TRAIL:{
            result = STEP_COLLISION;
        }
        break;
        case GAME_PLAYER:
            result = STEP_COLLISION;
        break;
        default:
            result = STEP_OK;
        break;
    }
    return result;
}

float generateRandomFloat()
{
    float r = (float)rand()/(float)RAND_MAX;
    return r;
}

void pursuePlayer(Player *enemy, int direction)
{
    if(direction == DIRECTION_VERTICAL)
    {
        if(mainPlayer.position.x > enemy->position.x)
            enemy->direction = DIRECTION_RIGHT;
        else
            enemy->direction = DIRECTION_LEFT;
    }
    else //HORIZONTAL
    {
        if(mainPlayer.position.y > enemy->position.y)
            enemy->direction = DIRECTION_DOWN;
        else
            enemy->direction = DIRECTION_UP;
    }
}

int translateElementDirection(int elementDirection)
{
    int newDirection;

    if((elementDirection == DIRECTION_LEFT) || (elementDirection == DIRECTION_RIGHT))
        newDirection = DIRECTION_HORIZONTAL;
    else
        newDirection = DIRECTION_VERTICAL;

    return newDirection;
}

void IAofEnemy(Player *enemy)
{
    int enemyStep = isStepOk(*enemy);
    float randomNumber;
    int direction = translateElementDirection(enemy->direction);

    if(enemyStep != STEP_OK)
    {
        decrementElementPosition(&(enemy->position), enemy->direction);

        switch(direction)
        {
            case DIRECTION_HORIZONTAL:
            {

                if((globalMatrix[enemy->position.x][enemy->position.y+1] == GAME_SPACE) && (globalMatrix[enemy->position.x][enemy->position.y-1] == GAME_SPACE))
                    pursuePlayer(enemy,DIRECTION_HORIZONTAL);
                else
                    if(globalMatrix[enemy->position.x][enemy->position.y+1] == GAME_SPACE)
                        enemy->direction = DIRECTION_DOWN;
                    else
                        if(globalMatrix[enemy->position.x][enemy->position.y-1] == GAME_SPACE)
                            enemy->direction = DIRECTION_UP;
                        else{
                            enemy->state = PLAYER_DEAD;
                            printf("\n Inimigo morreu \a\n");
                        }
            }
            break;
            case DIRECTION_VERTICAL:
            default:
            {
                if((globalMatrix[enemy->position.x+1][enemy->position.y] == GAME_SPACE) && (globalMatrix[enemy->position.x-1][enemy->position.y] == GAME_SPACE))
                    pursuePlayer(enemy,DIRECTION_VERTICAL);
                else
                    if(globalMatrix[enemy->position.x+1][enemy->position.y] == GAME_SPACE)
                        enemy->direction = DIRECTION_RIGHT;
                    else
                        if(globalMatrix[enemy->position.x-1][enemy->position.y] == GAME_SPACE)
                            enemy->direction = DIRECTION_LEFT;
                        else{
                            enemy->state = PLAYER_DEAD;
                            printf("\n Inimigo morreu \a\n");
                        }
            }
            break;
        }

        incrementElementPosition(&(enemy->position), enemy->direction);
    }
    else
    { //No collision, generate future step direction
        randomNumber = generateRandomFloat();

        //Inimigos perseguem o player
        if (randomNumber < 0.05 || randomNumber > 0.95)
        {
            if(direction == DIRECTION_HORIZONTAL)
                pursuePlayer(enemy, DIRECTION_HORIZONTAL);
            else
                pursuePlayer(enemy, DIRECTION_VERTICAL);
        }
    }
}

void incrementEnemyPosition(Player *enemy)
{
    if(enemy->state != PLAYER_DEAD){
        incrementElementPosition( &(enemy->position), enemy->direction );
        IAofEnemy(enemy);
    }
}

void updateEnemysPositions()
{
    if(enemy1.state != PLAYER_DEAD)
        globalMatrix[enemy1.position.x][enemy1.position.y] = GAME_ENEMY_1;
    else
        globalMatrix[enemy1.position.x][enemy1.position.y] = GAME_SPACE;

    if(enemy2.state != PLAYER_DEAD)
        globalMatrix[enemy2.position.x][enemy2.position.y] = GAME_ENEMY_2;
    else
        globalMatrix[enemy2.position.x][enemy2.position.y] = GAME_SPACE;
}

int verifyIfPlayerWon(int playerStep)
{
    int retorno=0;

    if(playerStep == STEP_OK)
        if((enemy1.state == PLAYER_DEAD) && (enemy2.state == PLAYER_DEAD))
            retorno = PLAYER_WON;
        else
            retorno = STEP_OK;
    else
        retorno = GAME_OVER;

    return retorno;
}

int gameStep()
{

    int playerStep;
    int gameStep;

    globalMatrix[mainPlayer.position.x][mainPlayer.position.y] = GAME_TRAIL;
	globalMatrix[enemy1.position.x][enemy1.position.y] = GAME_TRAIL;
	globalMatrix[enemy2.position.x][enemy2.position.y] = GAME_TRAIL;

    incrementElementPosition( &(mainPlayer.position), mainPlayer.direction );
    playerStep = isStepOk(mainPlayer);
    globalMatrix[mainPlayer.position.x][mainPlayer.position.y] = GAME_PLAYER;

    incrementEnemyPosition(&enemy1);
    incrementEnemyPosition(&enemy2);

    updateEnemysPositions();

    gameStep = verifyIfPlayerWon(playerStep);

    return gameStep;
}