#include "../includes/meshloader.h"

Vertex3D* loadBirosca()
{
    Vertex3D listVertex[11061];
    int i = 0;
    FILE * file = fopen("../models/TronBike/TronBike.obj", "r");
    if( file == NULL ){
        printf("Impossible to open the file !\n");
        return 0;
    }
    while(1)
    {
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (feof(file))
            break; // EOF = End Of File. Quit the loop.
        else if ( strcmp( lineHeader, "v" ) == 0 ){
            Vertex3D vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            listVertex[i] = vertex;
            i++;
        }
    }
    fclose(file);
    return listVertex;
}