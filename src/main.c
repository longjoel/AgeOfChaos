#include <stdio.h>

#include "video/video.h"

int main()
{
    VideoInit();
    VideoCleanup();
    printf("Hello\n");
    return 0;
}