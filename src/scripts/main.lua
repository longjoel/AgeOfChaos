-- main

local tileValues = {
    {passable=true, row=6, col=0, name="dirt"},
    {passable=true, row=6, col=1, name="dirt-grass"},
    {passable=true, row=6, col=2, name="grass"},
    {passable=false, row=7, col=0, name="rock", bg_row=6, bg_col=1},
}

local sprites = {{name="hero",
    col_start = 0,     col_end=1,    row_start=9,     row_end=10}}

local DrawSprite = function(i,x,y)
    local sprite = sprites[i]
    

    local row = sprite.row_start
    local col = sprite.col_start
    
    while row <= sprite.row_end +1 do

        while col <= sprite.col_end +1 do

            DrawTile(col, row, x + (col-sprite.col_start)*8,y+(row-sprite.row_start)*8,0)
           
            col =col+1
        end
        col = sprite.col_start
        row =row+1
    end
    
end

local level = {{}}

while true do
    local mouse = PollMouse()
    ClearBuffer()
    DrawString(mouse.x, mouse.y, ">")
    DrawString(mouse.x+8, mouse.y, "<")
    DrawSprite(1,0,0)
    SwapBuffers()

end
