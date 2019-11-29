#include <dos.h>

#include "input.h"

int PollKeyboard(void)
{
    union REGS regs;

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