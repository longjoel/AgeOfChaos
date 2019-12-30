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
    Log(sprite.name)
    Log("rows:"..sprite.row_start .." "..sprite.row_end)
    Log("cols:"..sprite.col_start .." "..sprite.col_end)
    local row =0
    local col = 0
    for row = sprite.row_start, sprite.row_end,1 do
        for col = sprites.col_start, sprite.col_end,1 do
            Log("row, col: "..row..", "..col)
            --DrawTile(row, col, x,y,0)
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
