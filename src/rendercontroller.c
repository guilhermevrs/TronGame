#include "../includes/rendercontroller.h"

void display() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderTerrain();
    glFlush();
}

void setVisionParameters(GLfloat aspect)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(90,aspect,0.1,500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f,150,1.0f, 0,0,0, 0,1,0);
}

void reshape(GLsizei w, GLsizei h) {
    if ( h == 0 ) h = 1;

    glViewport(0, 0, w, h);

    GLfloat fAspect = (GLfloat)w/(GLfloat)h;

    setVisionParameters(fAspect);
    anim(0);
}

//Usado para testes de parâmetros
void anim(int a)
{
    glutTimerFunc(200, anim, a);
}

void renderTerrain()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(105.0f,0.0f,-105.0f);
        glVertex3f(-105.0f,0.0f,-105.0f);
        glVertex3f(-105.0f,0.0f,105.0f);
        glVertex3f(105.0f,0.0f,105.0f);
    glEnd();
}

void initRender(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE);
    glutInitWindowSize (640, 480);
    glutCreateWindow ("TronGame");

    glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering

    glutReshapeFunc(reshape);
}