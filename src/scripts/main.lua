-- main

while true do
 
    local mouse = PollMouse()

    DrawTile(0, 0, mouse.x, mouse.y, 0)

    SwapBuffers()

end
