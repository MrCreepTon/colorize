local colorize = require('colorize_core')

addEventHandler('onScriptTerminate', function(script, quit)
    if script == thisScript() then
        colorize.unload()
    end
end)

colorize.colorPed = function(ped, r, g, b, a)
    assert(doesCharExist(ped), 'Ped does not exist')
    r = math.min(255, math.max(0, r))
    g = math.min(255, math.max(0, g))
    b = math.min(255, math.max(0, b))
    if a == nil then a = 255 end
    a = math.min(255, math.max(0, a))
    local pPed = getCharPointer(ped)
    colorize.color(pPed, r, g, b, a)
end

colorize.uncolorPed = function(ped)
    assert(doesCharExist(ped), 'Ped does not exist')
    local pPed = getCharPointer(ped)
    colorize.color(pPed)
end

return colorize