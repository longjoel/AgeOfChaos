#include <stdlib.h>

#include "video.h"

video_context _videoContext;

void VideoInit(){

    _videoContext.vga = (uint8_t* )(void *)0xA0000000;
    _videoContext.backBuffer = (uint8_t *)malloc(sizeof(uint8_t*)*320*200);

}

void VideoCleanup(){
    free(_videoContext.backBuffer);
}