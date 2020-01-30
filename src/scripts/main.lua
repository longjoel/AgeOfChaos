-- main
local ReadAll = function(file)
    local f = assert(io.open(file, "rb"))
    local content = f:read("*all")
    f:close()
    return content
end

local TitleScreen = load(ReadAll("scripts/tscrn.lua"))()
TitleScreen.onLoad()

local stateDictionary = {{name = 'titlescreen', value = TitleScreen}};

local stateStack = {TitleScreen}

local state = {
    pushState = function(stateName)
        table.insert(stateStack, stateDictionary[stateName].value)
    end,

    popState = function() stateStack[#stateStack] = nil end

}

Frame = function(t)
    local top = stateStack[#stateStack]

    if (top ~= nil) then top.onFrame(state) end
end

Render = function(t)
    ClearBuffer()
    local top = stateStack[#stateStack]

    if top == nil then
        QuitGame()
    else
        top.onRender(state)
    end
    SwapBuffers()
end
