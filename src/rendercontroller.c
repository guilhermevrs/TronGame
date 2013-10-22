#include "../includes/rendercontroller.h"

extern char globalMatrix[SCENE_HEIGHT][SCENE_WIDTH];

GLfloat ha, goi;
GLfloat aspect;

/*
    Display function for opengl
*/
void display() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderMatrix();
    glFlush();
}

/*
    Sets perspective view and came postion
*/
void setVisionParameters()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(90,aspect,0.1,500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f,130.0f,1.0f, 0,0,0, 0,1,0);
}

/*
    Reshape function for opengl
*/
void reshape(GLsizei w, GLsizei h) {
    if ( h == 0 ) h = 1;

    glViewport(0, 0, w, h);
    ha = 150.0f;
    goi = 10.0f;

    aspect = (GLfloat)w/(GLfloat)h;

    setVisionParameters();
}

/*
    Render wall
    linha = position in x
    coluna = position in y
*/
void renderWall(float linha, float coluna)
{
    glBegin(GL_LINES);

    glColor3f(1.0f,0.0f,0.0f);//wall color
    glVertex3f(linha,0.0f,coluna);
    glVertex3f(linha,10.0f,coluna);

    glEnd();
}

/*
    Render the player
    linha = position in x
    coluna = position in y
*/
void renderPlayer(float linha, float coluna)
{
    glBegin(GL_POINTS);

    glColor3f(0.0f,1.0f,0.0f);//player color
    glVertex3f(linha,0.0f,coluna);

    glEnd();
}

/*
    Renders the terrain
*/
void renderMatrix()
{
    int linha, coluna;
    float linhaInc, colunaInc, posLinha, posColuna;

    linhaInc = 110.0f/((float)SCENE_HEIGHT);
    colunaInc = 110.0f/((float)SCENE_WIDTH);

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 1.0f); //Terrain color
    glBegin(GL_QUADS);
        glVertex3f(110.0f,0.0f,-110.0f);
        glVertex3f(-110.0f,0.0f,-110.0f);
        glVertex3f(-110.0f,0.0f,110.0f);
        glVertex3f(110.0f,0.0f,110.0f);
    glEnd();

    for (linha = 0; linha < SCENE_HEIGHT; ++linha)
    {
        for (coluna = 0; coluna < SCENE_WIDTH; ++coluna)
        {
            posLinha = (2 * linhaInc * (float)linha) - 110.0f;
            posColuna = (2 * colunaInc * (float)coluna) - 110.0f;

            if(globalMatrix[linha][coluna] == GAME_WALL) //IS WALL?
                renderWall(posLinha, posColuna);
             else if(globalMatrix[linha][coluna] == GAME_PLAYER) //IS PLAYER?
                renderPlayer(posLinha, posColuna);
        }
    }
}

//Usado para testes de parâmetros
void anim(int a)
{
    gameStep();
    glutPostRedisplay();
    glutTimerFunc(200, anim, a);
}

void initRender(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE);
    glutInitWindowSize (640, 480);
    glutCreateWindow ("TronGame");

    glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering
    glutReshapeFunc(reshape);

    anim(0);

}