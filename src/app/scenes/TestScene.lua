local TestScene = class("TestScene", function()
    return display.newScene("TestScene")
end)

function TestScene:ctor()
    cc.ui.UILabel.new({
            UILabelType = 2, text = "TestScene", size = 64})
        :align(display.CENTER, display.cx, display.cy)
        :addTo(self)
end

function TestScene:onEnter()
end

function TestScene:onExit()
end

return TestScene