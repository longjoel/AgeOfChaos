-- main

while true do

    local x = math.random(319)
    local y = math.random(200)
    local c = math.random(255)
    
    SetPixel (x,y,c)

    SwapBuffers()
end