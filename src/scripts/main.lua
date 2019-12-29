-- main

while true do
 
    local mouse = PollMouse()
    ClearBuffer()
    DrawString(mouse.x, mouse.y, ">")
    DrawString(mouse.x+8, mouse.y, "<")

    SwapBuffers()

end
