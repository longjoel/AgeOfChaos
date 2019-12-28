#pragma once

#define TILE_SHEET_WIDTH    64
#define TILE_SHEET_HEIGHT   64

#define TILE_WIDTH          8       // width of a tile
#define TILE_HEIGHT         8       // height of tile

#include <stdint.h>

#include "../lua/lua.h"

typedef struct _video_context {
    uint8_t * vga;
    uint8_t *backBuffer;
    uint8_t *tileMemory;
    uint8_t *fontMemory;

} video_context;

void VideoInit();
void VideoCleanup();
void SwapBuffers();

void SetPixel(uint16_t x, uint16_t y, uint8_t c);
void SetTilePixel(uint16_t col, uint16_t row, uint16_t x, uint16_t y, uint8_t color);

void DrawTile(uint16_t col, uint16_t row, uint16_t x, uint16_t y, uint8_t transparentColor);

void DrawChar(uint16_t x, uint16_t y, uint8_t c);
void DrawString(uint16_t x, uint16_t y, const char *s);

void SetPalette(uint8_t index, uint8_t r, uint8_t g, uint8_t b);

void GetPalette(uint8_t index, uint8_t *r, uint8_t *g, uint8_t *b);

void ClearBuffer();


void LoadTiles(const char *path);

/*

LUA SCRIPT DEFINITIONS

*/

extern "C"{
    int L_SwapBuffers(lua_State *L);

    int L_SetPixel(lua_State *L);

    int L_SetTilePixel(lua_State *L);

    int L_DrawTile(lua_State *L);

    int L_LoadTiles(lua_State *L);

    int L_DrawString(lua_State *L);

    int L_ClearBuffer(lua_State *L);

}