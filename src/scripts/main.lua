-- main

while true do
 
    local mouse = PollMouse()
    ClearBuffer()
    DrawString(mouse.x, mouse.y, "Age of Chaos!")

    SwapBuffers()

end
