#include "../includes/rendercontroller.h"

extern char globalMatrix[SCENE_HEIGHT][SCENE_WIDTH];
extern Player mainPlayer;
extern unsigned char gameMode;
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
    Translates matrix line to 3D line
    linha = matrix line
*/
float translateLine(unsigned char linha)
{
    float linhaInc = 110.0f/((float)SCENE_HEIGHT);
    return (2 * linhaInc * (float)linha) - 110.0f;
}

/*
    Translates matrix column to 3D line
    coluna = matrix line
*/
float translateColumn(unsigned char coluna)
{
    float colunaInc = 110.0f/((float)SCENE_WIDTH);
    return (2 * colunaInc * (float)coluna) - 110.0f;
}

void set3rdVision()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float posLine = translateLine(mainPlayer.position.x);
    float posColumn = translateColumn(mainPlayer.position.y);

    gluLookAt(posLine - 5.0f, PLAYER_HEIGHT + CAMERA_3RD_DISTANCE ,posColumn, posLine,PLAYER_HEIGHT,posColumn, 0,1,0);
}

void setTopVision()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0f,130.0f,1.0f, 0,0,0, 0,1,0);
}

/*
    Sets perspective view and came postion
*/
void setVisionParameters()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(90,aspect,0.1,500);
    if(gameMode == GAME_MODE_TOP)
        setTopVision();
    else
        set3rdVision();
}

/*
    Reshape function for opengl
*/
void reshape(GLsizei w, GLsizei h) {
    if ( h == 0 ) h = 1;

    glViewport(0, 0, w, h);

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
    glVertex3f(linha,WALL_HEIGHT,coluna);

    glEnd();
}

/*
    Render the player
    linha = position in x
    coluna = position in y
*/
void renderPlayer(float linha, float coluna)
{
    glPointSize(4.0f);
    glBegin(GL_POINTS);

    glColor3f(0.0f,1.0f,0.0f);//player color
    glVertex3f(linha,PLAYER_HEIGHT,coluna);

    glEnd();
}

/*
    Renders the terrain
*/
void renderMatrix()
{
    unsigned char linha, coluna;
    float linhaInc, colunaInc, posLinha, posColuna;

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
            posLinha = translateLine(linha);
            posColuna = translateColumn(coluna);

            if(globalMatrix[linha][coluna] == GAME_WALL) //IS WALL?
                renderWall(posLinha, posColuna);
             else if(globalMatrix[linha][coluna] == GAME_PLAYER) //IS PLAYER?
                renderPlayer(posLinha, posColuna);
        }
    }
}

//Usado para o loop do jogo
void animateGame(int a)
{
    gameStep();
    if(gameMode == GAME_MODE_3D)
        set3rdVision();
    else
        setTopVision();
    glutPostRedisplay();
    glutTimerFunc(200, animateGame, a);
}

void initRender(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE);
    glutInitWindowSize (640, 480);
    glutCreateWindow ("TronGame");

    glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering
    glutReshapeFunc(reshape);

    animateGame(0);

}