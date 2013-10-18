#include <stdlib.h> // for EXIT_SUCCESS
#include <stdio.h> // for printf and scanf
#include <string.h>

#include <GL/glut.h> // OpenGL Utility Toolkit - for using the Windowing system
#include <GL/gl.h> // OpenGL - for rendering 3D graphics
#include <GL/glu.h> // OpenGL Utility Library - extra features built atop of GL

#include "../includes/defines.h"
#include "../includes/matrixcontroller.h"


extern Player mainPlayer;

void display() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
    glutPostRedisplay();
}

void commonKeyPressed (unsigned char key, int x, int y) {
    printf("common: %c\n",key);
}

void specialKeyPressed (int key, int x, int y) {
    switch(key)
    {
        case KEY_LEFT: mainPlayer.direction = DIRECTION_LEFT;   break;
        case KEY_UP: mainPlayer.direction = DIRECTION_UP;   break;
        case KEY_RIGHT: mainPlayer.direction = DIRECTION_RIGHT;   break;
        case KEY_DOWN: mainPlayer.direction = DIRECTION_DOWN;  break;
        default: break;
    }
}

int main (int argc, char *argv[]) {

  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (640, 480);
  glutCreateWindow ("TRON Game");
  glutDisplayFunc (&display);

  glutKeyboardFunc(commonKeyPressed);
  glutSpecialFunc(specialKeyPressed);

  initGameMatrix();

  glutIdleFunc(gameStep);

  glutMainLoop();

  glDisable (GL_TEXTURE_2D);

  return EXIT_SUCCESS;
}