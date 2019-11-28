#include <stdio.h>

#include "video/video.h"

int main(int nArgs, char **args)
{
    VideoInit();
    
    for(;;){
        printf ("Butts");
    }

    VideoCleanup();
    printf("Hello\n");
    return 0;
}