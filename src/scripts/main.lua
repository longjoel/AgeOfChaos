-- main
local TitleScreen = require("titlescreen.lua")

local state = {}

local stateStack = {TitleScreen}

for v,_ in stateStack do
    v.onLoad()
end

while table.getn(stateStack) > 0 do
    local top = stateStack(#stateStack)

    top.onFrame(state)

    top.onRender(state)
end
