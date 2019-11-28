#include <stdio.h>
 #include <dpmi.h>
 #include <stdlib.h>
 #include <string.h>
#include "video/video.h"

int main(int nArgs, char **args)
{
   
__dpmi_regs regs;

memset(&regs, 0, sizeof regs);
regs.x.ax = 0x13; /* 0x13 is the mode number */
__dpmi_int(0x10, &regs);


    VideoInit();

    for(int c = 0; c < 256; c++){
        SetPallet(c,(c*2)%255,(c/2)%255,c);
    }
    
    for(;;){
        for(int q = 0; q < 255; q++){
            

            
            for(int i = 0; i < 320; i++){
                for(int j = 0; j < 200; j++){
                    SetPixel(i,j, (uint8_t)(((i%200)+(j%200)+q * (i/2*j/2))%255));
                }
            }

        SwapBuffers();
    }}

    VideoCleanup();
    printf("Hello\n");
    return 0;
}