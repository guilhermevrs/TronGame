#ifndef MATRIXCONTROLLER_H
#define MATRIXCONTROLLER_H 1

#include <stdio.h>
#include "defines.h"

typedef struct{
    unsigned char x;
    unsigned char y;
} Position;

typedef struct{
    Position position;
    unsigned char direction;
} Player;

/*
    Initializes the game matrix
*/
void initGameMatrix();
/*
    Performs a step in the game machine state
    val = value required by opengl (can be 0)

    Returns:   STEP_OK - Everything fine
                    STEP_COLLISION - Player colided
*/
int gameStep();

#endif