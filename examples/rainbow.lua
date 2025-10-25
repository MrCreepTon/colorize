-- Example of usage: Making rainbow peds.

local colorize = require('colorize') -- include our libraries

-- Some constants
local SPEED = 2
local ALPHA = 255
local OFFSET = 100

function main()
    while true do
        wait(0)
        local i = 0
        for _, ped in pairs(getAllChars()) do
            i = i + OFFSET
            rainbowPed(ped, i)
        end
    end
end

function rainbowPed(ped, modify)
    local r, g, b, a = rainbow(SPEED, ALPHA, modify)
    -- Colorizing ped (r, g, b, a)
    colorize.colorPed(ped, r, g, b, a)
end

-- Generate rainbow color
function rainbow(speed, alpha, modify)
    if not modify then modify = 0 end
    local time = os.clock() + modify
    return math.floor(math.sin(time * speed) * 127 + 128), math.floor(math.sin(time * speed + 2) * 127 + 128), math.floor(math.sin(time * speed + 4) * 127 + 128), alpha
end