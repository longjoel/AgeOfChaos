local TitleScreen = {
    onLoad = function()
    end,

    onRender = function(state)

        -- age of chaos
        DrawTileRange(0,0,
        17,3,
        88,72,
        0)

        DrawString(72,128,"Press `Space` to begin")
    end,

    onFrame = function(state)
    end
}

return TitleScreen;