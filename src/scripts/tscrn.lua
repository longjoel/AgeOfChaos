
local frameCount = 0
local animationDirection = 1.0
local animationX = 15.0
local animationFrames = {{col=0, row=9, cols=2, rows=2},
    {col=2, row=9, cols=2, rows=2}}

local TitleScreen = {
    onLoad = function()
    end,

    onRender = function(state)

        -- age of chaos
        DrawTileRange(0,0,
        17,3,
        88,72,
        0)

        local slowFrameCount = 2+( frameCount//1000)
        local frame = animationFrames[(slowFrameCount % #animationFrames)+1]
        DrawTileRange(frame.col, frame.row, frame.cols, frame.rows, math.floor(animationX),0,0)
        DrawTileRange(frame.col, frame.row, frame.cols, frame.rows, math.floor(314-animationX),184,0)

        DrawString(72,128,"Press `Space` to begin")
    end,

    onFrame = function(state)

        frameCount = frameCount + 1
        animationX = animationX + (animationDirection * 0.05)

        if (animationX <=0) then
            animationX = 1
            animationDirection = 1
        end

        if (animationX >= 304) then
            animationX = 303
            animationDirection = -1
        end



    end
}

return TitleScreen;