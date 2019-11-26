#pragma once
#ifndef __AOC_INPUT_H__
#define __AOC_INPUT_H__

#include "../sys/sys.h"

#define LMB (0x01)
#define RMB (0x02)

#define KBD_UP  (0x001)
#define KBD_DOWN  (0x002)
#define KBD_LEFT (0x003)
#define KBD_RIGHT (0x004)

#define KBD_1 (0x71)    /* Q */
#define KBD_2 (0x77)    /* W */
#define KBD_3 (0x65)    /* E */
#define KBD_4 (0x72)    /* R */

#define KBD_ESC (0x1B)  /* escape */
#define KBD_RET (0x0D)  /* return */

typedef struct _mouse_state  mouse_state;

void PollMouseState(mouse_state *mouseState);

BOOL PollKeyboardState(BYTE key);

void InitInput();

#endif