#include <stdlib.h>
#include <string.h>
#include "../sys/sys.h"
#include "video.h"

static video_system_vars _video;


void InitVideo(){

    _video.vga = (BYTE *)(void *)0xA0000000;
    _video.backBuffer = (BYTE *)malloc(sizeof(BYTE*) *320*200);

    asm("int $10h"
        : /*NOOP*/
        :"ah"(0x00), "al"(0x10)
        : /*NOOP*/);

}

void CleanupVideo(){
      asm("int $10h"
        : /*NOOP*/
        :"ah"(0x00), "al"(0x03)
        : /*NOOP*/);

    free(_video.backBuffer);
}

void SwapBuffers(){
    memcpy(_video.vga, _video.backBuffer, sizeof(BYTE*)*320*200);

}