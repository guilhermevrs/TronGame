#ifndef RENDERCONTROLLER_H
#define RENDERCONTROLLER_H 1

#include <GL/glut.h> // OpenGL Utility Toolkit - for using the Windowing system
#include <GL/gl.h> // OpenGL - for rendering 3D graphics
#include <GL/glu.h> // OpenGL Utility Library - extra features built atop of GL

#include "matrixcontroller.h"
#include "defines.h"
#include "meshloader.h"

/*
    Initialize Rendercontroller
*/
void initRender(int argc, char *argv[]);
void renderMatrix();

#endif