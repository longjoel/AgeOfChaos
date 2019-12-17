#include <dos.h>
#include <stdint.h>

#include "input.h"

uint8_t PollKeyboard(void)
{
    union REGS regs;

    static bool isInit = false;

    if (!isInit)
    {
        regs.h.al = 0x05;
        regs.h.ah = 0x03;
        regs.h.bh = 0x00;
        regs.h.bl = 0x00;
        int86(0x16, &regs, &regs); /* do it! */

        isInit = true;
    }

    regs.h.ah = 0x01;
    int86(0x16, &regs, &regs); /* do it! */

    int key = regs.h.ah;

    if (key != 0 && key != 1)
    {
        regs.h.ah = 0x00;
        int86(0x16, &regs, &regs); /* do it! */
    }
    return key;
}

void PollMouse(uint8_t *buttons, uint16_t *x, uint16_t *y)
{
    union REGS regs;

    static bool isInit = false;

    if (!isInit)
    {

        regs.w.ax = 0x000;
        int86(0x33, &regs, &regs); /* do it! */
        isInit = true;
    }

    regs.w.ax = 0x003;
    int86(0x33, &regs, &regs); /* do it! */

    *x = regs.w.cx / 2;
    *y = regs.w.dx;
    *buttons = regs.w.bx;
}

extern "C"
{

    int L_PollKeyboard(lua_State *L)
    {
        uint8_t result = PollKeyboard();

        lua_pushnumber(L, result);

        return 1;

    }

    int L_PollMouse(lua_State *L)
    {
        uint8_t buttons;
        uint16_t x;
        uint16_t y;

        PollMouse(&buttons, &x, &y);

        lua_newtable(L);

        lua_pushliteral(L, "buttons");
        lua_pushnumber(L, buttons);
        lua_settable(L, -3); /* 3rd element from the stack top */

        lua_pushliteral(L, "x");
        lua_pushnumber(L, x);
        lua_settable(L, -3);

        lua_pushliteral(L, "y");
        lua_pushnumber(L, y);
        lua_settable(L, -3);

        return 1;
    }
}