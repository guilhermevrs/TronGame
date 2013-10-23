#ifndef TEXTUREHELPER_H
#define TEXTUREHELPER_H 1

#include <stdio.h>

#include <GL/glut.h> // OpenGL Utility Toolkit - for using the Windowing system
#include <GL/gl.h> // OpenGL - for rendering 3D graphics
#include <GL/glu.h> // OpenGL Utility Library - extra features built atop of GL

/*
    Loads texture from bmp
    imagepath = Local do bmp da texture

    Retorna o ID da texture
*/
GLuint loadBMP_custom(const char * imagepath);

#endif