#pragma once

#define MAX_SCREEN_SPRITES  16      // maximum number of sprites on the screen
#define MAX_TILES           64      // maximum number of tiles in a sheet
#define MAX_PALLET          4       // each tile gets 4 colors    

#define TILEMAP_WIDTH       50      // tile map width (in tiles)
#define TILEMAP_HEIGHT      30      // tile map height (int tiles)

#define TILE_WIDTH          8       // width of a tile
#define TILE_HEIGHT         8       // height of tile

#include <stdint.h>

typedef struct _sprite_context {
    bool enabled;
    bool transparent;
    uint16_t x;
    uint16_t y;
} sprite_context;

typedef struct _video_context {
    uint8_t * vga;
    uint8_t *backBuffer;
    sprite_context *sprites;

    uint8_t *tileMemory;
    uint8_t *tileMapMemory;

    bool wrap_tiles;

} video_context;



void VideoInit();

void VideoCleanup();

void SwapBuffers();

void SetPixel(uint16_t x, uint16_t y, uint8_t c);

void SetPalette(uint8_t index, uint8_t r, uint8_t g, uint8_t b);

void GetPalette(uint8_t index, uint8_t *r, uint8_t *g, uint8_t *b);

void PutStr(uint8_t col, uint8_t row, char * str);

void SetSpriteAttributes(uint8_t index, sprite_context *spriteContext);
void GetSpriteAttributes(uint8_t index, sprite_context *spriteContext);

void SetTilePalette(uint8_t spriteIndex, 
    uint8_t palette, 
    uint8_t r, uint8_t g, uint8_t b);