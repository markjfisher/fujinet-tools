#include <string.h>
#include <stdio.h>
#include "main.h"
#include "nget.h"

const char *version = "1.0.0";

char source[256];
char dest[256];

void get_parms(void)
{
    printf("Enter Source URL: \n");
    gets(source);

    if (!source[0])
        return;
    
    printf("Enter Destination Filename: \n");
    gets(dest);

    if (!dest[0])
        return;
}

int main(int argc, char* argv[])
{
    if (argc<2)
        get_parms();
    else
    {
        strcpy(source,argv[1]);
        strcpy(dest,argv[2]);
    }
    
    if (!source[0])
    {
        printf("Source not specified. Exiting.\n");
        return 1;
    }

    if (!dest[0])
    {
        printf("Destination not specified. Exiting.\n");
        return 1;
    }

    return nget(source, dest);
}
