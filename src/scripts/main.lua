-- main
local ReadAll = function(file)
    local f = assert(io.open(file, "rb"))
    local content = f:read("*all")
    f:close()
    return content
end

local TitleScreen = load(ReadAll("scripts/tscrn.lua"))()
TitleScreen.onLoad()

local state = {}

local stateStack = {TitleScreen}

Frame = function(t)
    local top = stateStack[#stateStack]

    top.onFrame(state)
end

Render = function(t)
    ClearBuffer()
    local top = stateStack[#stateStack]

    top.onRender(state)

    DrawString(0,0,tostring(t))
    SwapBuffers()
end
