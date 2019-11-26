#pragma once
#ifndef __AOC_VIDEO_H__
#define __AOC_VIDEO_H__

#include "../sys/sys.h"

typedef struct _video_system_vars {
    BYTE *vga;
    BYTE *backBuffer;
} video_system_vars;

typedef struct _rect {
    UINT32 x;
    UINT32 y;
    UINT32 w;
    UINT32 h;

} rect;

void InitVideo();
void CleanupVideo();

#endif