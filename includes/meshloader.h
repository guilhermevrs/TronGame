#include <stdio.h>

#include <GL/glut.h> // OpenGL Utility Toolkit - for using the Windowing system
#include <GL/gl.h> // OpenGL - for rendering 3D graphics
#include <GL/glu.h> // OpenGL Utility Library - extra features built atop of GL

typedef struct{
    float x;
    float y;
    float z;
} Vertex3D;

Vertex3D* loadBirosca();