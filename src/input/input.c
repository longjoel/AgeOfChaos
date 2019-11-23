#include "../sys/sys.h"
#include "input.h"

#include <conio.h>
#include <stdio.h>

void PollMouseState(mouse_state_t *mouseState)
{
}

BOOL PollKeyboardState(BYTE key)
{

    switch (key)
    {
    case KBD_UP:
    case KBD_DOWN:
    case KBD_LEFT:
    case KBD_RIGHT:

        if (!getch())
        {
            int nextCh = getch();
            switch (nextCh)
            {
            case 72:
                return (key == KBD_UP);
            case 75:
                return (key == KBD_DOWN);
            case 77:
                return (key == KBD_RIGHT);
            case 80:
                return (key == KBD_LEFT);
            }
        }
        return FALSE;
        break;

    default:
        return key == getch();
        break;
    }
}

void InitInput()
{
}