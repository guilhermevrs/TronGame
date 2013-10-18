#include "filehelper.h"

/*
    PRIVATE FUNCTIONS
*/

/*
    END OF PRIVATE FUNCTIONS
*/

    int openFile(FILE* file, char* fileName, char* fileMode)
    {
        file = fopen(fileName, fileMode);
        if(file == NULL)
            return 0;
        else
            return 1;
    }