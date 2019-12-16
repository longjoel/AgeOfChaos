#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <sys/nearptr.h>
#include "video.h"

#define PALETTE_INDEX 0x03c8
#define PALETTE_DATA 0x03c9
#define INPUT_STATUS 0x03da

video_context _videoContext;

void VideoInit()
{

    __djgpp_nearptr_enable();

    union REGS regs;

    regs.h.ah = 0x00;          /* function 00h = mode set */
    regs.h.al = 0x13;          /* 256-color */
    int86(0x10, &regs, &regs); /* do it! */

    _videoContext.vga = (uint8_t *)(void *)(0xA0000 + __djgpp_conventional_base);
    _videoContext.backBuffer = (uint8_t *)malloc(320 * 200);

    _videoContext.tileMemory = (uint8_t *)malloc(TILE_WIDTH * TILE_HEIGHT * TILE_SHEET_WIDTH * TILE_SHEET_HEIGHT);
}

void VideoCleanup()
{
    free(_videoContext.backBuffer);

    union REGS regs;

    regs.h.ah = 0x00;          /* function 00h = mode set */
    regs.h.al = 0x03;          /* 256-color */
    int86(0x10, &regs, &regs); /* do it! */

    __djgpp_nearptr_disable();
}

void SetPixel(uint16_t x, uint16_t y, uint8_t c)
{
    _videoContext.backBuffer[(y << 8) + (y << 6) + x] = c;
}

void SwapBuffers()
{
    memcpy(_videoContext.vga, _videoContext.backBuffer, 320 * 200);
}

void SetPalette(uint8_t index, uint8_t r, uint8_t g, uint8_t b)
{

    outp(PALETTE_INDEX, index);
    outp(PALETTE_DATA, r);
    outp(PALETTE_DATA, g);
    outp(PALETTE_DATA, b);
}

void SetTilePixel(uint16_t col,
                  uint16_t row,
                  uint16_t x, uint16_t y, uint8_t color)
{

    _videoContext.tileMemory[(((row * 8) + y) * 512) + (col * 8) + (x)] = color;
}

void DrawTile(uint16_t col,
                uint16_t row,
                uint16_t x, uint16_t y, uint8_t transparentColor)
{
    for (int yy = 0; yy < 8; yy++)
    {
        for (int xx = 0; xx < 8; xx++)
        {
            uint8_t c = _videoContext.tileMemory[(((row * 8) + yy) * 512) + (col * 8) + (xx)];
            if (c != transparentColor && (y + yy) >= 0 && (y + yy < 200) && (x + xx >= 0) && (x + xx < 320))
            {
                _videoContext.backBuffer[((y + yy) * 320) + (x + xx)] = c;
            }
        }
    }
}

void GetPalette(uint8_t index, uint8_t *r, uint8_t *g, uint8_t *b)
{
    outp(PALETTE_INDEX, index);
    *r = inp(PALETTE_DATA);
    *g = inp(PALETTE_DATA);
    *b = inp(PALETTE_DATA);
}

void PutStr(uint8_t col, uint8_t row, char *str)
{
    union REGS regs;

    regs.h.ah = 0x02;
    regs.h.bh = 0x00;
    regs.h.dh = row;
    regs.h.dl = col;

    int86(0x10, &regs, &regs);

    printf(str);
}

/*
LUA functions
*/

extern "C"
{
    int L_SwapBuffers(lua_State *L)
    {

        SwapBuffers();
        return 0;
    }

    int L_SetPixel(lua_State *L)
    {

        double x = lua_tonumber(L, 1);
        double y = lua_tonumber(L, 2);
        double c = lua_tonumber(L, 3);

        SetPixel((uint16_t)x, (uint16_t)y, (uint8_t)c);
        return 0;
    }

    int L_SetTilePixel(lua_State *L)
    {
        double col = lua_tointeger(L, 1);
        double row = lua_tointeger(L, 2);
        double x = lua_tointeger(L, 3);
        double y = lua_tointeger(L, 4);
        double c = lua_tointeger(L, 5);

        SetTilePixel(col, row, x, y, c);

        return 0;
    }

    int L_DrawTile(lua_State *L)
    {
        double col = lua_tointeger(L, 1);
        double row = lua_tointeger(L, 2);
        double x = lua_tointeger(L, 3);
        double y = lua_tointeger(L, 4);
        double c = lua_tointeger(L, 5);

        DrawTile(col, row, x, y, c);
        return 0;
    }
}