#pragma once

#include <stdint.h>

typedef struct _video_context {
    uint8_t * vga;
    uint8_t *backBuffer;
    
} video_context;

void VideoInit();

void VideoCleanup();

void SwapBuffers();

void SetPixel(uint16_t x, uint16_t y, uint8_t c);

void SetPallet(uint8_t index, uint8_t r, uint8_t g, uint8_t b);

void GetPallet(uint8_t index, uint8_t *r, uint8_t *g, uint8_t *b);

void PutChar(uint8_t col, uint8_t row, char c);