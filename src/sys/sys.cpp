#include <stdio.h>
#include <dpmi.h>
#include <stdlib.h>
#include <string.h>

#include "sys.h"

void SysInit(){
     __dpmi_regs regs;

    memset(&regs, 0, sizeof regs);
    regs.x.ax = 0x13; /* 0x13 is the mode number */
    __dpmi_int(0x10, &regs);

}