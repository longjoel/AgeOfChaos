#pragma once

#include <stdint.h>

typedef struct _video_context {
    uint8_t * vga;
    uint8_t *backBuffer;
    
} video_context;

void VideoInit();

void VideoCleanup();