#include <dos.h>
#include <stdint.h>

#include "input.h"

uint8_t PollKeyboard(void)
{
    union REGS regs;

    static bool isInit = false;

    if(!isInit){
        regs.h.al = 0x05;
        regs.h.ah = 0x03;
        regs.h.bh = 0x00;
        regs.h.bl= 0x00;
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

    if(!isInit){

        regs.w.ax = 0x000;
        int86(0x33, &regs, &regs); /* do it! */
        isInit = true;
    }


    regs.w.ax = 0x003;
    int86(0x33, &regs, &regs); /* do it! */

    *x = regs.w.cx/2;
    *y = regs.w.dx;
    *buttons = regs.w.bx;
}