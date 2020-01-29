#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <sys/nearptr.h>
#include "video.h"

#include "../sys/sys.h"

#define PALETTE_INDEX 0x03c8
#define PALETTE_DATA 0x03c9
#define INPUT_STATUS 0x03da

typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;

typedef struct tagBITMAP /* the structure for a bitmap. */
{
    word width;
    word height;
    byte *data;
} BITMAP;

void fskip(FILE *fp, int num_bytes)
{
    int i;
    for (i = 0; i < num_bytes; i++)
        fgetc(fp);
}

video_context _videoContext;

void VideoInit()
{

    // __djgpp_nearptr_enable();

    union REGS regs;

    regs.h.ah = 0x00;          /* function 00h = mode set */
    regs.h.al = 0x13;          /* 256-color */
    int86(0x10, &regs, &regs); /* do it! */

    _videoContext.vga = (uint8_t *)(void *)(0xA0000 + __djgpp_conventional_base);
    _videoContext.backBuffer = (uint8_t *)malloc(320 * 200);

    _videoContext.tileMemory = (uint8_t *)malloc(TILE_WIDTH * TILE_HEIGHT * TILE_SHEET_WIDTH * TILE_SHEET_HEIGHT);
    _videoContext.fontMemory = (uint8_t *)malloc(512 * 512);
}

void VideoCleanup()
{
    free(_videoContext.backBuffer);
    // TODO: clear tile memory and font memory

    union REGS regs;

    regs.h.ah = 0x00;          /* function 00h = mode set */
    regs.h.al = 0x03;          /* 256-color */
    int86(0x10, &regs, &regs); /* do it! */

    // __djgpp_nearptr_disable();
}

void SetPixel(uint16_t x, uint16_t y, uint8_t c)
{
    _videoContext.backBuffer[(y << 8) + (y << 6) + x] = c;
}

void SwapBuffers()
{
    // todo: wait for vsync
    memcpy(_videoContext.vga, _videoContext.backBuffer, 320 * 200);
}

void ClearBuffer()
{
    memset(_videoContext.backBuffer, 0, 320 * 200);
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

void DrawTileRange(uint16_t col, uint16_t row,
                   uint16_t cols, uint16_t rows,
                   uint16_t x, uint16_t y,
                   uint8_t transparentColor)
{
    for (int yy = 0; yy < 8 * rows; yy++)
    {
        for (int xx = 0; xx < 8 * cols; xx++)
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

void DrawChar(uint16_t x, uint16_t y, uint8_t c)
{
    int col = 0;
    int row = 0;

    if (c >= 'A' && c <= 'Z')
    {
        col = (c - 'A') + 17;
        row = 0;
    }
    if (c >= 'a' && c <= 'z')
    {
        col = (c - 'a') + 17;
        row = 1;
    }
    const char *row3 = "`1234567890-=[]\\;',./ ";
    if (strchr(row3, c))
    {
        int index = strchr(row3, c) - row3;
        row = 2;
        col = index + 17;
    }
    const char *row4 = "~!@#$%^&*()_+{}|:\"<>?";

    if (strchr(row4, c))
    {
        int index = strchr(row4, c) - row4;
        row = 3;
        col = index + 17;
    }
    DrawTile(col, row, x, y, 0);
}

void DrawString(uint16_t x, uint16_t y, const char *s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        DrawChar(x + (i * 8), y, s[i]);
    }
}

void LoadTiles(const char *file)
{
    FILE *fp;
    long index;
    word num_colors;
    int x;
    BITMAP bx;
    BITMAP *b = &bx;

    /* open the file */
    if ((fp = fopen(file, "rb")) == NULL)
    {
        printf("Error opening file %s.\n", file);
        exit(1);
    }

    /* check to see if it is a valid bitmap file */
    if (fgetc(fp) != 'B' || fgetc(fp) != 'M')
    {
        fclose(fp);
        printf("%s is not a bitmap file.\n", file);
        exit(1);
    }

    /* read in the width and height of the image, and the
     number of colors used; ignore the rest */
    fskip(fp, 16);
    fread(&b->width, sizeof(word), 1, fp);
    fskip(fp, 2);
    fread(&b->height, sizeof(word), 1, fp);
    fskip(fp, 22);
    fread(&num_colors, sizeof(word), 1, fp);
    fskip(fp, 6);

    /* assume we are working with an 8-bit file */
    if (num_colors == 0)
        num_colors = 256;

    if (b->width != 512 && b->height != 512)
    {
        fclose(fp);
        printf("Wrong size for file %s. Should be 512x512\n", file);
        exit(1);
    }

    for (index = 0; index < num_colors; index++)
    {
        SetPalette(index, fgetc(fp) >> 2, fgetc(fp) >> 2, fgetc(fp) >> 2);
        fgetc(fp);
    }

    /* read the bitmap */
    for (index = (b->height - 1) * b->width; index >= 0; index -= b->width)
        for (x = 0; x < b->width; x++)
            _videoContext.tileMemory[(word)index + x] = (byte)fgetc(fp);

    fclose(fp);
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
        uint16_t col = lua_tointeger(L, 1);
        uint16_t row = lua_tointeger(L, 2);
        uint16_t x = lua_tonumber(L, 3);
        uint16_t y = lua_tonumber(L, 4);
        uint16_t c = lua_tointeger(L, 5);

        DrawTile(col, row, x, y, c);
        return 0;
    }

    int L_DrawTileRange(lua_State *L)
    {
        uint16_t col = lua_tointeger(L, 1);
        uint16_t row = lua_tointeger(L, 2);
        uint16_t cols = lua_tointeger(L, 3);
        uint16_t rows = lua_tointeger(L, 4);
        uint16_t x = lua_tonumber(L, 5);
        uint16_t y = lua_tonumber(L, 6);
        uint16_t c = lua_tointeger(L, 7);

        DrawTileRange(col, row, cols, rows, x, y, c);
        return 0;
    }

    int L_LoadTiles(lua_State *L)
    {
        const char *file = lua_tostring(L, 1);
        LoadTiles(file);
        return 0;
    }

    int L_DrawString(lua_State *L)
    {
        double x = lua_tointeger(L, 1);
        double y = lua_tointeger(L, 2);
        const char *s = lua_tostring(L, 3);
        DrawString(x, y, s);
        return 0;
    }

    int L_ClearBuffer(lua_State *L)
    {
        ClearBuffer();
        return 0;
    }
}