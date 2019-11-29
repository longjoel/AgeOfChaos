#include <stdio.h>
#include <dpmi.h>
#include <stdlib.h>
#include <string.h>
#include "sys/sys.h"
#include "video/video.h"
#include "input/input.h"

int main(int nArgs, char **args)
{

    SysInit();

    VideoInit();

    for (int c = 0; c < 256; c++)
    {
        SetPallet(c, (c * 2) % 255, (c / 2) % 255, c);
    }

    for (;;)
    {
        for (int q = 0; q < 255; q++)
        {

            for (int i = 0; i < 320; i++)
            {
                for (int j = 0; j < 200; j++)
                {
                    SetPixel(i, j, (uint8_t)(((i % 200) + (j % 200) + q * (i / 2 * j / 2)) % 255));
                }
            }

            SwapBuffers();

            if(PollKeyboard()== KBD_UP){
                return 0;
            }
        }
    }

    VideoCleanup();
    printf("Hello\n");
    return 0;
}