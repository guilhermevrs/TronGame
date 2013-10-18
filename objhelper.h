#ifndef OBJHELPER_H
#define OBJHELPER_H 1

#include <string.h>
#include "filehelper.h"

#define LINE_MAX_LENGTH 100

/*

*/

typedef struct {
  float x, y, z;
} Vertex3D;

typedef struct {
  float x, y;
} Vertex2D;

/*---------------------------FUNCTIONS*/

void parseObjFile(char* fileName, Vertex3D vertexArray[]);

#endif
