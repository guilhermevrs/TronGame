#include "../includes/rendercontroller.h"

extern char globalMatrix[SCENE_HEIGHT][SCENE_WIDTH];
extern Player mainPlayer;
extern Player enemy1;
extern Player enemy2;
extern unsigned char gameMode;
int stopGame;
GLfloat aspect;
GLuint textureWallID;
GLuint textureTrailID;
GLuint textureFloorID;
GLuint textureBikeBlueID;
GLuint textureBikeRedID;

float linhaInc = WORLD_SIDE/((float)SCENE_HEIGHT);
float colunaInc = WORLD_SIDE/((float)SCENE_WIDTH);

/*
    Display function for opengl
*/
void display() {
   	//glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glClear (GL_DEPTH_BUFFER_BIT);
    glScissor(200,0,600,450);
    glEnable(GL_SCISSOR_TEST);
    //set3rdVision();
    glViewport(200,0, 600, 450);
    renderMatrix();
    glDisable(GL_SCISSOR_TEST);
    //glutSwapBuffers();

        glClear (GL_DEPTH_BUFFER_BIT);
        glEnable(GL_SCISSOR_TEST);
        glScissor(-50,250,250,250);
        setTopVision();
        glViewport(-50,250, 300, 300);
    if(gameMode == GAME_MODE_3D)
    {
        renderMatrix();
    }
    else
    {
        clearViewport();
    }
    glDisable(GL_SCISSOR_TEST);
    glutSwapBuffers();

}

/*
    Translates matrix line to 3D line
    linha = matrix line
*/
float translateLine(unsigned char linha)
{
    return (2 * linhaInc * (float)linha) - WORLD_SIDE;
}

/*
    Translates matrix column to 3D line
    coluna = matrix line
*/
float translateColumn(unsigned char coluna)
{
    return (2 * colunaInc * (float)coluna) - WORLD_SIDE;
}

void set3rdVision()
{
    float posLine = translateLine(mainPlayer.position.x);
    float posColumn = translateColumn(mainPlayer.position.y);

    float posXCamera;
    float posZCamera;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    switch(mainPlayer.direction)
    {
        case DIRECTION_RIGHT:
        default:
            posXCamera = posLine - CAMERA_3RD_DISTANCE;
            posZCamera = posColumn;
        break;
        case DIRECTION_DOWN:
            posXCamera = posLine;
            posZCamera = posColumn - CAMERA_3RD_DISTANCE;
        break;
        case DIRECTION_LEFT:
            posXCamera = posLine + CAMERA_3RD_DISTANCE;
            posZCamera = posColumn;
        break;
        case DIRECTION_UP:
            posXCamera = posLine;
            posZCamera = posColumn + CAMERA_3RD_DISTANCE;
        break;
    }

    gluLookAt(posXCamera, PLAYER_HEIGHT + CAMERA_3RD_DISTANCE ,posZCamera, posLine,PLAYER_HEIGHT,posColumn, 0,1,0);
}

void setTopVision()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0f,CAMERA_TOP_DISTANCE,1.0f, 0,0,0, 0,1,0);
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

    glViewport(150, 0, 550, 450);
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
    float linhaNeg = linha - linhaInc;
    float linhaPos = linha + linhaInc;
    float colunaNeg = coluna - colunaInc;
    float colunaPos = coluna + colunaInc;


    glColor3f(0.7372f, 0.8666f, 0.9882f);
    glBindTexture(GL_TEXTURE_2D, textureWallID);
    //FRONT
    glBegin(GL_POLYGON);

    glNormal3d(0, 0, 1);
    glTexCoord2f (0.0, 0.0);
    glVertex3f(  linhaPos, 0.1, colunaNeg );
    glTexCoord2f (1.0, 0.0);
    glVertex3f(  linhaPos,  WALL_HEIGHT, colunaNeg );
    glTexCoord2f (1.0, 1.0);
    glVertex3f( linhaNeg,  WALL_HEIGHT, colunaNeg );
    glTexCoord2f (0.0, 1.0);
    glVertex3f( linhaNeg, 0.1, colunaNeg );

    glEnd();

    // BACK
    glBegin(GL_POLYGON);
    glNormal3d(0, 0, -1);
    glTexCoord2f (1.0, 1.0);
    glVertex3f(  linhaPos, 0.1f, colunaPos );
    glTexCoord2f (0.0, 1.0);
    glVertex3f(  linhaPos,  WALL_HEIGHT, colunaPos );
    glTexCoord2f (0.0, 0.0);
    glVertex3f( linhaNeg,  WALL_HEIGHT, colunaPos );
    glTexCoord2f (1.0, 0.0);
    glVertex3f( linhaNeg, 0.1f, colunaPos );
    glEnd();

    // RIGHT
    glBegin(GL_POLYGON);
    glNormal3d(1, 0, 0);
    glTexCoord2f (1.0, 0.0);
    glVertex3f( linhaPos, 0.1f, colunaNeg );
    glTexCoord2f (0.0, 1.0);
    glVertex3f( linhaPos,  WALL_HEIGHT, colunaNeg );
    glTexCoord2f (0.0, 0.0);
    glVertex3f( linhaPos,  WALL_HEIGHT,  colunaPos );
    glTexCoord2f (1.0, 1.0);
    glVertex3f( linhaPos, 0.1f,  colunaPos );
    glEnd();

    // LEFT
    glBegin(GL_POLYGON);
    glNormal3d(-1, 0, 0);
    glTexCoord2f (1.0, 1.0);
    glVertex3f( linhaNeg, 0.1f,  colunaPos );
    glTexCoord2f (0.0, 0.0);
    glVertex3f( linhaNeg,  WALL_HEIGHT,  colunaPos );
    glTexCoord2f (0.0, 1.0);
    glVertex3f( linhaNeg,  WALL_HEIGHT, colunaNeg );
    glTexCoord2f (1.0, 0.0);
    glVertex3f( linhaNeg, 0.1f, colunaNeg );
    glEnd();

    // TOP
    glBegin(GL_POLYGON);
    glNormal3d(0, 1, 0);
    glTexCoord2f (0.0, 1.0);
    glVertex3f(  linhaPos,  WALL_HEIGHT,  colunaPos );
    glTexCoord2f (1.0, 1.0);
    glVertex3f(  linhaPos,  WALL_HEIGHT, colunaNeg );
    glTexCoord2f (0.0, 0.0);
    glVertex3f( linhaNeg,  WALL_HEIGHT, colunaNeg );
    glTexCoord2f (1.0, 0.0);
    glVertex3f( linhaNeg,  WALL_HEIGHT,  colunaPos );
    glEnd();

    // BOTTOM
    glBegin(GL_POLYGON);
    glNormal3d(0, -1, 0);
    glTexCoord2f (0.0, 0.0);
    glVertex3f(  linhaPos, 0.1f, colunaNeg );
    glTexCoord2f (1.0, 0.0);
    glVertex3f(  linhaPos, 0.1f,  colunaPos );
    glTexCoord2f (0.0, 1.0);
    glVertex3f( linhaNeg, 0.1f,  colunaPos );
    glTexCoord2f (1.0, 1.0);
    glVertex3f( linhaNeg, 0.1f, colunaNeg );
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
}

/*
    Render the player
    linha = position in x
    coluna = position in y
*/
void renderPlayer(float linha, float coluna)
{

    loadBike(mainPlayer.direction, "models/TronBike/TronBike.obj", linha, coluna, textureBikeBlueID);

}

/*
    Render the enemy
    linha = position in x
    coluna = position in y
*/
void renderEnemy(float linha, float coluna, Player enemy)
{
    loadBike(enemy.direction, "models/TronBike/TronBike.obj", linha, coluna, textureBikeRedID);
}

void renderTrail(float linha, float coluna)
{
    float linhaNeg = linha - linhaInc;
    float linhaPos = linha + linhaInc;
    float colunaNeg = coluna - colunaInc;
    float colunaPos = coluna + colunaInc;

    glColor3f(0.7372f, 0.8666f, 0.9882f);//trail color
    glBindTexture(GL_TEXTURE_2D, textureTrailID);
    glBegin(GL_POLYGON);

    //FRONT
    glNormal3d(0, 0, 1);
    glTexCoord2f (0.0, 0.0);
    glVertex3f(  linhaPos, 0.1, colunaNeg );
    glTexCoord2f (1.0, 0.0);
    glVertex3f(  linhaPos,  TRAIL_HEIGHT, colunaNeg );
    glTexCoord2f (1.0, 1.0);
    glVertex3f( linhaNeg,  TRAIL_HEIGHT, colunaNeg );
    glTexCoord2f (0.0, 1.0);
    glVertex3f( linhaNeg, 0.1, colunaNeg );

    glEnd();

    // BACK
    glBegin(GL_POLYGON);
    glNormal3d(0, 0, -1);
    glTexCoord2f (1.0, 1.0);
    glVertex3f(  linhaPos, 0.1f, colunaPos );
    glTexCoord2f (0.0, 1.0);
    glVertex3f(  linhaPos,  TRAIL_HEIGHT, colunaPos );
    glTexCoord2f (0.0, 0.0);
    glVertex3f( linhaNeg,  TRAIL_HEIGHT, colunaPos );
    glTexCoord2f (1.0, 0.0);
    glVertex3f( linhaNeg, 0.1f, colunaPos );
    glEnd();

    // RIGHT
    glBegin(GL_POLYGON);
    glNormal3d(1, 0, 0);
    glTexCoord2f (1.0, 0.0);
    glVertex3f( linhaPos, 0.1f, colunaNeg );
    glTexCoord2f (0.0, 1.0);
    glVertex3f( linhaPos,  TRAIL_HEIGHT, colunaNeg );
    glTexCoord2f (0.0, 0.0);
    glVertex3f( linhaPos,  TRAIL_HEIGHT,  colunaPos );
    glTexCoord2f (1.0, 1.0);
    glVertex3f( linhaPos, 0.1f,  colunaPos );
    glEnd();

    // LEFT
    glBegin(GL_POLYGON);
    glNormal3d(-1, 0, 0);
    glTexCoord2f (1.0, 1.0);
    glVertex3f( linhaNeg, 0.1f,  colunaPos );
    glTexCoord2f (0.0, 0.0);
    glVertex3f( linhaNeg,  TRAIL_HEIGHT,  colunaPos );
    glTexCoord2f (0.0, 1.0);
    glVertex3f( linhaNeg,  TRAIL_HEIGHT, colunaNeg );
    glTexCoord2f (1.0, 0.0);
    glVertex3f( linhaNeg, 0.1f, colunaNeg );
    glEnd();

    // TOP
    glBegin(GL_POLYGON);
    glNormal3d(0, 1, 0);
    glTexCoord2f (0.0, 1.0);
    glVertex3f(  linhaPos,  TRAIL_HEIGHT,  colunaPos );
    glTexCoord2f (1.0, 1.0);
    glVertex3f(  linhaPos,  TRAIL_HEIGHT, colunaNeg );
    glTexCoord2f (0.0, 0.0);
    glVertex3f( linhaNeg,  TRAIL_HEIGHT, colunaNeg );
    glTexCoord2f (1.0, 0.0);
    glVertex3f( linhaNeg,  TRAIL_HEIGHT,  colunaPos );
    glEnd();

    // BOTTOM
    glBegin(GL_POLYGON);
    glNormal3d(0, -1, 0);
    glTexCoord2f (0.0, 0.0);
    glVertex3f(  linhaPos, 0.1f, colunaNeg );
    glTexCoord2f (1.0, 0.0);
    glVertex3f(  linhaPos, 0.1f,  colunaPos );
    glTexCoord2f (0.0, 1.0);
    glVertex3f( linhaNeg, 0.1f,  colunaPos );
    glTexCoord2f (1.0, 1.0);
    glVertex3f( linhaNeg, 0.1f, colunaNeg );
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void clearViewport()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    glClearColor (0.0, 0.0, 0.0, 0.0);
}

/*
    Renders the terrain
*/
void renderMatrix()
{
    unsigned char linha, coluna;
    float posLinha, posColuna;

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.7372f, 0.8666f, 0.9882f); //Terrain color
    glBindTexture(GL_TEXTURE_2D, textureFloorID);
    glBegin(GL_QUADS);
        glNormal3d(0, 1, 0);
        glTexCoord2f (0.0f, 0.0f);
        glVertex3f(WORLD_SIDE,0.0f,-WORLD_SIDE);
        glTexCoord2f (1.0f, 0.0f);
        glVertex3f(-WORLD_SIDE,0.0f,-WORLD_SIDE);
        glTexCoord2f (1.0f, 1.0f);
        glVertex3f(-WORLD_SIDE,0.0f,WORLD_SIDE);
        glTexCoord2f (0.0f, 1.0f);
        glVertex3f(WORLD_SIDE,0.0f,WORLD_SIDE);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    for (linha = 0; linha < SCENE_HEIGHT; ++linha)
    {
        for (coluna = 0; coluna < SCENE_WIDTH; ++coluna)
        {
            posLinha = translateLine(linha);
            posColuna = translateColumn(coluna);

            if(globalMatrix[linha][coluna] == GAME_WALL) //IS WALL?
                renderWall(posLinha,posColuna);
             else if(globalMatrix[linha][coluna] == GAME_PLAYER) //IS PLAYER?
                renderPlayer(posLinha, posColuna);
			 else if(globalMatrix[linha][coluna] == GAME_ENEMY_1) //IS ENEMY?
				    renderEnemy(posLinha, posColuna, enemy1);
                  else
                    if(globalMatrix[linha][coluna] == GAME_ENEMY_2)
                        renderEnemy(posLinha, posColuna, enemy2);
             else if(globalMatrix[linha][coluna] == GAME_TRAIL)
                renderTrail(posLinha, posColuna);
        }
    }
}

//Usado para o loop do jogo
void animateGame(int a)
{
    int gameIsOver = 0;
    if(stopGame != 1)
        gameIsOver = gameStep();
    if(gameMode == GAME_MODE_3D)
        set3rdVision();
    else
        setTopVision();
    glutPostRedisplay();
    if(gameIsOver != GAME_OVER)
        if(gameIsOver != PLAYER_WON)
            glutTimerFunc(100, animateGame, a);
        else{
            printf("Congratulations! You WON!\n");
            exit(1);
        }
    else
    {
        printf("Game Is OVER!\n");
        exit(1);
    }
}

void initRender(int argc, char *argv[])
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 0.0 };
    GLfloat light0_position[] = { 0.0, CAMERA_TOP_DISTANCE, 0.0, 0.0 };

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (800, 600);
    glutCreateWindow ("TronGame");

    glEnable (GL_TEXTURE_2D);

    textureWallID = loadBMP_custom("models/textures/wall-texture.bmp");
    textureTrailID = loadBMP_custom("models/textures/trail-texture.bmp");
    textureFloorID = loadBMP_custom("models/textures/floor-texture.bmp");
    textureBikeBlueID = loadBMP_custom("models/TronBike/bike blue.bmp");
    textureBikeRedID = loadBMP_custom("models/TronBike/bike red.bmp");

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering
    glutReshapeFunc(reshape);

    animateGame(0);
}