#ifndef RENDERCONTROLLER_H
#define RENDERCONTROLLER_H 1

#include <GL/glut.h> // OpenGL Utility Toolkit - for using the Windowing system
#include <GL/gl.h> // OpenGL - for rendering 3D graphics
#include <GL/glu.h> // OpenGL Utility Library - extra features built atop of GL


/*
    Initialize Rendercontroller
*/
void initRender(void);

/*
    Render the game terrain
*/
void RenderTerrain();

void display();
void reshape( int w, int h);

#endif