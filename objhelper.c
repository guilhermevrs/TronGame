#include "objhelper.h"

/*--------------------------PRIVATE FUNCTIONS*/

Vertex3D parseVertex(char* line)
{
     Vertex3D v;
      sscanf (line, "v %f %f %f", v.x, v.y, v.z);
      return v;
}

/*--------------------------END OF PRIVATE FUNCTIONS*/


void parseObjFile(char* fileName, Vertex3D vertexArray[])
{
    FILE* file;
    char line[LINE_MAX_LENGTH];
    int iVertex = 0;
    if(openFile(file, fileName, "r"))
    {
        while(fgets(line, LINE_MAX_LENGTH, file) != NULL)
        {
            if(strncmp (line, "v ", 2) == 0) //Vertice
            {
                vertexArray[iVertex] = parseVertex(line);
                iVertex++;
            }
        }
    }
}