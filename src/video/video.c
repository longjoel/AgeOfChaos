#include <stdlib.h>
#include <string.h>
#include "../sys/sys.h"
#include "video.h"

struct _video_system_vars {
    BYTE *vga;
    BYTE *backBuffer;
};

struct _video_system_vars _video ;


void InitVideo(){

    _video = {
        .vga = (BYTE *)(void *)0xA0000000,
        .backBuffer =(BYTE *)malloc(sizeof(BYTE*) *320*200)
    };
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