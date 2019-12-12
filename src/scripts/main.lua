-- main

local i = 0

while true do


    local x = math.random(319)
    local y = math.random(200)
    local r = (i/360)*(2*math.pi)

    local newX1 = 160 + (50)*math.cos(r) - (50)*math.sin(r);
    local newY1 = 100 + (50)*math.sin(r) + (50)*math.cos(r);


    local newX2 = 160 + (25)*math.cos(-r/2) - (25)*math.sin(-r/2);
    local newY2 = 100 + (25)*math.sin(-r/2) + (25)*math.cos(-r/2);


    local c = i%255
    local c2 = 255-c
    
    SetPixel (newX1,newY1,c)
    SetPixel (newX2,newY2,c2)

    SwapBuffers()

    i = i+1;
end