#pragma once

#include <stdint.h>
#include "../lua/lua.h"

#define KBD_UP 0x68
#define KBD_DOWN 0x70
#define KBD_LEFT 0x6B
#define KBD_RIGHT 0x6D


uint8_t PollKeyboard(void);

#define MOUSE_LEFT 0x01
#define MOUSE_RIGHT 0x02;

void PollMouse (uint8_t *buttons, uint16_t *x, uint16_t *y);

extern "C"{
    int L_PollKeyboard(lua_State *L);
    int L_PollMouse(lua_State *L);
}