-- main
local smileyface = {}
smileyface[1] = {1, 1, 1, 1, 1, 1, 1, 1}
smileyface[2] = {1, 1, 1, 1, 1, 1, 1, 1}
smileyface[3] = {1, 1, 1, 1, 1, 1, 1, 1}
smileyface[4] = {1, 1, 1, 1, 1, 1, 1, 1}
smileyface[5] = {1, 1, 1, 1, 1, 1, 1, 1}
smileyface[6] = {1, 1, 1, 1, 1, 1, 1, 1}
smileyface[7] = {1, 1, 1, 1, 1, 1, 1, 1}
smileyface[8] = {1, 1, 1, 1, 1, 1, 9, 1}

for y = 0, 7 do
    for x = 0, 7 do SetTilePixel(0, 0, x, y, smileyface[y + 1][x + 1]) end
end

while true do
    local x = 0
    local y = 0
    local mouseIsClicked = false

    local mouse = {x = 0, y = 0, buttons = 0}
    mouse = PollMouse()

    DrawTile(0, 0, mouse.x, mouse.y, 0)

    SwapBuffers()

end
