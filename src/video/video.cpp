#include <stdlib.h>
#include <dos.h>
#include "video.h"

video_context _videoContext;

void VideoInit(){


    union REGS regs;

    regs.h.ah = 0x00;  /* function 00h = mode set */
    regs.h.al = 0x13;  /* 256-color */
    int86(0x10,&regs,&regs); /* do it! */

    _videoContext.vga = (uint8_t* )(void *)0xA0000000;
    _videoContext.backBuffer = (uint8_t *)malloc(sizeof(uint8_t*)*320*200);

}

void VideoCleanup(){
    free(_videoContext.backBuffer);

     union REGS regs;

    regs.h.ah = 0x00;  /* function 00h = mode set */
    regs.h.al = 0x03;  /* 256-color */
    int86(0x10,&regs,&regs); /* do it! */
}