#include <dos.h>
#include <conio.h>

#include "input.h"

int PollKeyboard(void)
   {
   int head, tail;
   unsigned int code;
   
   head = peek(0x40, 0x1A);
   tail = peek(0x40, 0x1C);
   
   if(head == tail)
      return(0);
   
   code = (peek(0x40,head) & 0xFF);
   if(code == 0)                       /*  extended char */
      code = (peek(0x40,head) & 0xFF00);
   
   if(head < 60)
      poke(0x40,0x1A,(head += 2));
   else
      poke(0x40,0x1A,(head = 30));
   
   return(code);
   }