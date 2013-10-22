#include "../includes/matrixcontroller.h"

char globalMatrix[SCENE_HEIGHT][SCENE_WIDTH];

Player mainPlayer;

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
    mainPlayer.direction = DIRECTION_RIGHT;
    globalMatrix[0][0] = GAME_PLAYER;

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

int gameStep()
{
    globalMatrix[mainPlayer.position.x][mainPlayer.position.y] = GAME_SPACE;
    incrementElementPosition( &(mainPlayer.position), mainPlayer.direction );
    globalMatrix[mainPlayer.position.x][mainPlayer.position.y] = GAME_PLAYER;
}