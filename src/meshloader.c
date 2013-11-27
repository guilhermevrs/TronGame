#include "../includes/meshloader.h"

void loadBike(unsigned char direction, char* nomeArquivo, float linha, float coluna, GLuint textureID)
{
    int iVertex = 0, iNormal = 0, iTexture = 0;
    int indexFace[3][3];
    Vertex3D vertex[728];
    Vertex3D normalVector[1304];
    Vertex2D textureVector[388];
    FILE * file = fopen(nomeArquivo, "r");
    if( file == NULL ){
        printf("Impossible to open the file !\n");
        exit(0);
    }

    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTranslatef(linha,5.0f,coluna);

    switch(direction)
    {
        case DIRECTION_RIGHT:
        default:
            glRotatef(90.0f, 0, 1, 0);
        break;
        case DIRECTION_DOWN:
            glRotatef(0.0f, 0, 1, 0);
        break;
        case DIRECTION_LEFT:
            glRotatef(-90.0f, 0, 1, 0);
        break;
        case DIRECTION_UP:
            glRotatef(180.0f, 0, 1, 0);
        break;
    }

    glScalef(0.7f,0.7f,0.7f);
    while(1)
    {
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (feof(file))
            break; // EOF = End Of File. Quit the loop.
        else if ( strcmp( lineHeader, "v" ) == 0 ){
            fscanf(file, "%f %f %f\n", &(vertex[iVertex].x), &(vertex[iVertex].y), &(vertex[iVertex].z) );
            iVertex++;
        }
        else if ( strcmp( lineHeader, "vn" ) == 0 ){
            fscanf(file, "%f %f %f\n", &(normalVector[iNormal].x), &(normalVector[iNormal].y), &(normalVector[iNormal].z) );
            iNormal++;
        }
        else if ( strcmp( lineHeader, "vt" ) == 0 ){
            fscanf(file, "%f %f\n", &(textureVector[iTexture].x), &(textureVector[iTexture].y) );
            iTexture++;
        }
        else if ( strcmp( lineHeader, "f" ) == 0 ){
            fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &indexFace[0][0], &indexFace[0][1], &indexFace[0][2], &indexFace[1][0], &indexFace[1][1], &indexFace[1][2], &indexFace[2][0], &indexFace[2][1], &indexFace[2][2] );

            glBegin(GL_TRIANGLES);
            glNormal3d(normalVector[ indexFace[0][2] - 1 ].x, normalVector[ indexFace[0][2] - 1 ].y, normalVector[ indexFace[0][2] - 1 ].z);

            glTexCoord2f (textureVector[ indexFace[0][1] - 1 ].x, textureVector[ indexFace[0][1] - 1 ].y);
            glVertex3f(vertex[indexFace[0][0]-1].x,vertex[indexFace[0][0]-1].y,vertex[indexFace[0][0]-1].z);

            glTexCoord2f (textureVector[ indexFace[1][1] - 1 ].x, textureVector[ indexFace[1][1] - 1 ].y);
            glVertex3f(vertex[indexFace[1][0]-1].x,vertex[indexFace[1][0]-1].y,vertex[indexFace[1][0]-1].z);

            glTexCoord2f (textureVector[ indexFace[2][1] - 1 ].x, textureVector[ indexFace[2][1] - 1 ].y);
            glVertex3f(vertex[indexFace[2][0]-1].x,vertex[indexFace[2][0]-1].y,vertex[indexFace[2][0]-1].z);
            glEnd();
        }
    }
    fclose(file);

    glPopMatrix();
}