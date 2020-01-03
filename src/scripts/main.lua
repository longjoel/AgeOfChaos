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
    

    local row_start = sprite.row_start
    local col_start = sprite.col_start
    local row_end = sprite.row_end
    local col_end = sprite.col_end
    
    for row= row_start,row_end do
        for col=col_start,col_end do
            DrawTile(col, row, x + (col-sprite.col_start)*8,y+(row-sprite.row_start)*8,0)
        end
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
