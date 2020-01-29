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

Frame = function ()
    
end

Render = function ()
end


-- while #stateStack > 0 do
--     local top = stateStack[#stateStack]

--     top.onFrame(state)

--     ClearBuffer()

--     top.onRender(state)

--     SwapBuffers()
-- end
