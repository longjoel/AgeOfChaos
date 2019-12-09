#include <stdio.h>
#include <dpmi.h>
#include <stdlib.h>
#include <string.h>
#include "sys/sys.h"
#include "video/video.h"
#include "input/input.h"

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

int main(int nArgs, char **args)
{

    SysInit();

    VideoInit();

    lua_State *L;

    /*
     * All Lua contexts are held in this structure. We work with it almost
     * all the time.
     */
    L = luaL_newstate();

    luaL_openlibs(L); /* Load Lua libraries */

    /* Load the file containing the script we are going to run */
    int status = luaL_loadfile(L, "scripts/main.lua");
    if (status) {
        /* If something went wrong, error message is at the top of */
        /* the stack */
        fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(L, -1));
        exit(1);
    }

    lua_register(L, "SwapBuffers", L_SwapBuffers);
    lua_register(L, "SetPixel", L_SetPixel);
    lua_register(L, "SetTilePallet", L_SetTilePalette);
    lua_register(L, "SetTilePixel", L_SetTilePixel);

    /* Ask Lua to run our little script */
    int result =lua_pcall(L, 0, LUA_MULTRET, 0);
    if (result) {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
        exit(1);
    }

    lua_close(L);   /* Cya, Lua */

while(true){}

    VideoCleanup();
    printf("Hello\n");
    return 0;
}