#include <stdio.h>
#include <dpmi.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <sys/nearptr.h>

#include "sys.h"

void SysInit(){
    //  __dpmi_regs regs;

    // memset(&regs, 0, sizeof regs);
    // regs.x.ax = 0x13; /* 0x13 is the mode number */
    // __dpmi_int(0x10, &regs);

}

void Log(const char *value){
    FILE *fptr = fopen("log.txt", "a");
    fprintf(fptr, value);
    fprintf(fptr, "\n");
    fclose(fptr);
}

const uint16_t *timerPtr = (uint16_t*)(0x046C + __djgpp_conventional_base);

uint16_t GetTime(){
    const float fTime = *(timerPtr);
    const float factor = 18.8f;
    return (uint16_t)floor( 1000* fTime/factor);
}
