#include <stdlib.h> // for EXIT_SUCCESS
#include <stdio.h> // for printf and scanf
#include <string.h>

#include <GL/glut.h> // OpenGL Utility Toolkit - for using the Windowing system
#include <GL/gl.h> // OpenGL - for rendering 3D graphics
#include <GL/glu.h> // OpenGL Utility Library - extra features built atop of GL

#include "../includes/defines.h"
#include "../includes/matrixcontroller.h"
#include "../includes/rendercontroller.h"

extern Player mainPlayer;
extern Player enemy1;
extern Player enemy2;
extern int stopGame;
unsigned char gameMode;


void commonKeyPressed (unsigned char key, int x, int y) {
    switch (key)
    {
        case 'v': case 'V':
            switch(gameMode)
            {
                case GAME_MODE_TOP: gameMode = GAME_MODE_3D;break;
                case GAME_MODE_3D: gameMode = GAME_MODE_FP;break;
                case GAME_MODE_FP: gameMode = GAME_MODE_TOP;break;
            }
        break;
        case 's': case 'S': stopGame = 1; break;
        case 'n': case 'N':
            stopGame = 0;
            break;
        default:
            stopGame = 0;
    }
    if(key == 'v' || key == 'V')
    {
        switch(gameMode)
        {
            case GAME_MODE_TOP: gameMode = GAME_MODE_3D;break;
            case GAME_MODE_3D: gameMode = GAME_MODE_FP;break;
            case GAME_MODE_FP: gameMode = GAME_MODE_TOP;break;
        }
    }
    else if(key == 's' || key == 'S')
            stopGame = 1;
    else
    {
            stopGame = 0;

    }
}

void specialKeyPressed (int key, int x, int y) {
    if(gameMode == GAME_MODE_TOP)
    {
        switch(key)
        {
            case KEY_LEFT: mainPlayer.direction = DIRECTION_LEFT;   break;
            case KEY_UP: mainPlayer.direction = DIRECTION_UP;   break;
            case KEY_RIGHT: mainPlayer.direction = DIRECTION_RIGHT;   break;
            case KEY_DOWN: mainPlayer.direction = DIRECTION_DOWN;  break;
            default: break;
        }
    }
    else
    {
        if(key == KEY_RIGHT)
        {
            switch(mainPlayer.direction)
            {
                case DIRECTION_LEFT: mainPlayer.direction = DIRECTION_UP;   break;
                case DIRECTION_UP: mainPlayer.direction = DIRECTION_RIGHT;   break;
                case DIRECTION_RIGHT: mainPlayer.direction = DIRECTION_DOWN;   break;
                case DIRECTION_DOWN: mainPlayer.direction = DIRECTION_LEFT;  break;
                default: break;
            }
        }
        else if(key == KEY_LEFT)
        {
            switch(mainPlayer.direction)
            {
                case DIRECTION_LEFT: mainPlayer.direction = DIRECTION_DOWN;   break;
                case DIRECTION_UP: mainPlayer.direction = DIRECTION_LEFT;   break;
                case DIRECTION_RIGHT: mainPlayer.direction = DIRECTION_UP;   break;
                case DIRECTION_DOWN: mainPlayer.direction = DIRECTION_RIGHT;  break;
                default: break;
            }
        }
    }
}

int main (int argc, char *argv[]) {

    gameMode = GAME_MODE_TOP;
    srand(time(NULL)); //preciso que o seed fique aqui
    initGameMatrix("grid");

    initRender(argc, argv);
    glutKeyboardFunc(commonKeyPressed);
    glutSpecialFunc(specialKeyPressed);

    glutMainLoop();

    return EXIT_SUCCESS;
}