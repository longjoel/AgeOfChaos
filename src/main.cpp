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

lua_CFunction frameFunc = nullptr;
lua_CFunction renderFunc = nullptr;

bool isRunning;

int L_Log(lua_State *L)
{
    const char *message = lua_tostring(L, 1);
    Log(message);
    return 0;
}

int L_QuitGame(lua_State *L){
    isRunning = false;
    return 0;
}

int main(int nArgs, char **args)
{

    SysInit();

    VideoInit();

    LoadTiles("images/aoc.bmp");

    lua_State *L;

    /*
     * All Lua contexts are held in this structure. We work with it almost
     * all the time.
     */
    L = luaL_newstate();

    lua_atpanic(L, L_Log);

    luaL_openlibs(L); /* Load Lua libraries */

    /* Load the file containing the script we are going to run */
    int status = luaL_loadfile(L, "scripts/main.lua");
    if (status)
    {
        /* If something went wrong, error message is at the top of */
        /* the stack */
        const char *error = lua_tostring(L, -1);
        fprintf(stderr, "Couldn't load file: %s\n", error);
        // Log(error);
        // exit(0);
    }

    // Register Log functions
    lua_register(L, "Log", L_Log);

    // Register video functions
    lua_register(L, "SwapBuffers", L_SwapBuffers);
    lua_register(L, "SetPixel", L_SetPixel);
    lua_register(L, "SetTilePixel", L_SetTilePixel);
    lua_register(L, "DrawTile", L_DrawTile);
    lua_register(L, "DrawTileRange", L_DrawTileRange);
    lua_register(L, "DrawString", L_DrawString);
    lua_register(L, "ClearBuffer", L_ClearBuffer);
    lua_register(L,"QuitGame", L_QuitGame);

    // Register input functions

    lua_register(L, "PollKeyboard", L_PollKeyboard);
    lua_register(L, "PollMouse", L_PollMouse);

    /* Ask Lua to run our little script */
    int result = lua_pcall(L, 0, LUA_MULTRET, 0);
    if (result)
    {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(L, -1));
        exit(1);
    }

    isRunning = true;
    while (isRunning == true)
    {
        const uint16_t time = GetTime();
        lua_getglobal(L, "Frame");
        lua_pushnumber(L, time);
            lua_call(L, 1, 0);

        lua_getglobal(L, "Render");
        lua_pushnumber(L, time);
        lua_call(L, 1, 0);
    }

    lua_close(L); /* Cya, Lua */

    VideoCleanup();

    printf("Thank you for playing Age of Chaos.\n\n");
    printf("Age of Chaos - code and art by Joel Longanecker.");

    return 0;
}