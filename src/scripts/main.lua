-- main

LoadTiles('images/hello.bmp')

while true do
    local x = 0
    local y = 0
    local mouseIsClicked = false

    local mouse = {x = 0, y = 0, buttons = 0}
    mouse = PollMouse()

    DrawTile(0, 0, mouse.x, mouse.y, 0)

    SwapBuffers()

end
