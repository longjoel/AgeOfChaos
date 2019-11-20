/**************************************************************************
 * pixel.c                                                                *
 * written by David Brackeen                                              *
 * http://www.brackeen.com/home/vga/                                      *
 *                                                                        *
 * Tab stops are set to 2.                                                *
 * This program compiles with DJGPP! (www.delorie.com)                    *
 * To compile in DJGPP: gcc pixel.c -o pixel.exe                          *
 *                                                                        *
 * This program will only work on DOS- or Windows-based systems with a    *
 * VGA, SuperVGA, or compatible video adapter.                            *
 *                                                                        *
 * Please feel free to copy this source code.                             *
 *                                                                        *
 * DESCRIPTION: This program demostrates how much faster writing directly *
 * to video memory is.                                                    *
 **************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <sys/nearptr.h>

#include "video.h"

word *my_clock = (word *)0x046C;      /* this points to the 18.2hz system
                                         clock. */

/**************************************************************************
 *  Main                                                                  *
 *    Plots 50000 pixels two different ways: using the BIOS and by        *
 *    directly writing to video memory.                                   *
 **************************************************************************/

void main()
{
  int x,y,color;
  float t1,t2;
  word i,start;

  if (__djgpp_nearptr_enable() == 0)
  {
    printf("Could get access to first 640K of memory.\n");
    exit(-1);
  }

  my_clock = (void *)my_clock + __djgpp_conventional_base;

  srand(*my_clock);                   /* seed the number generator. */


  t1=(*my_clock-start)/18.2;          /* calculate how long it took. */

  set_mode(VGA_256_COLOR_MODE);       /* set the video mode again in order
                                         to clear the screen. */

  start=*my_clock;                    /* record the starting time. */
  for(i=0;i<50000L;i++)               /* randomly plot 50000 pixels. */
  {
    x=rand()%SCREEN_WIDTH;
    y=rand()%SCREEN_HEIGHT;
    color=rand()%NUM_COLORS;
    plot_pixel_fast(x,y,color);
  }

  t2=(*my_clock-start)/18.2;          /* calculate how long it took. */
  
  for(;;);
  
  set_mode(TEXT_MODE);                /* set the video mode back to
                                         text mode. */

  

  __djgpp_nearptr_disable();

  return;
}