#ifndef MESHLOADER_H

#define MESHLOADER_H 0
#include <stdio.h>
#include "defines.h"
#include <GL/glut.h> // OpenGL Utility Toolkit - for using the Windowing system
#include <GL/gl.h> // OpenGL - for rendering 3D graphics
#include <GL/glu.h> // OpenGL Utility Library - extra features built atop of GL

typedef struct{
    float x;
    float y;
    float z;
} Vertex3D;

typedef struct{
    float x;
    float y;
} Vertex2D;

/*
Loads the bike
*/
void loadBike(unsigned char direction, char* nomeArquivo, float linha, float coluna, GLuint textureID);

#endif