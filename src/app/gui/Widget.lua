local Widget = class("Widget", function()
    return display.newNode()
end)

function Widget:ctor()
    self:setAnchorPoint(0.5, 0.5)
end

return Widget