#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <sys/nearptr.h>
#include "video.h"


#define PALETTE_INDEX       0x03c8
#define PALETTE_DATA        0x03c9
#define INPUT_STATUS        0x03da

video_context _videoContext;

void VideoInit(){

    __djgpp_nearptr_enable() ;

    union REGS regs;

    regs.h.ah = 0x00;  /* function 00h = mode set */
    regs.h.al = 0x13;  /* 256-color */
    int86(0x10,&regs,&regs); /* do it! */

    _videoContext.vga = (uint8_t* )(void *)(0xA0000 + __djgpp_conventional_base);
    _videoContext.backBuffer = (uint8_t *)malloc(320*200);

}

void VideoCleanup(){
    free(_videoContext.backBuffer);

     union REGS regs;

    regs.h.ah = 0x00;  /* function 00h = mode set */
    regs.h.al = 0x03;  /* 256-color */
    int86(0x10,&regs,&regs); /* do it! */
    
    __djgpp_nearptr_disable() ;

}

void SetPixel(uint16_t x, uint16_t y, uint8_t c){
     _videoContext.backBuffer[(y<<8) + (y<<6) + x] = c;
}

void SwapBuffers(){
   memcpy(_videoContext.vga, _videoContext.backBuffer, 320*200);
}

void SetPallet(uint8_t index, uint8_t r, uint8_t g, uint8_t b){

    outp(PALETTE_INDEX,index);            
    outp(PALETTE_DATA,r);   
    outp(PALETTE_DATA,g);
    outp(PALETTE_DATA,b);   
}


void GetPallet(uint8_t index, uint8_t *r, uint8_t *g, uint8_t *b){
 outp(PALETTE_INDEX,index);            
    *r = inp(PALETTE_DATA);   
    *g = inp(PALETTE_DATA);   
    *b = inp(PALETTE_DATA);   
}
