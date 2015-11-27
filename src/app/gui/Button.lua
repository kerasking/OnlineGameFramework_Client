local State = {
    Normal = 0,
    Pressed = 1,
    Disabled = 2
}

local Widget = require("app.gui.Widget")
local Button = class("Button", Widget)

function Button:ctor()
    Button.super.ctor(self)
    -- self:addNodeEventListener(cc.NODE_TOUCH_EVENT, handler(self, self.onTouch_))

    self._img_normal = nil
    self._img_pressed = nil
    self._img_disabled = nil

    self._txt_normal = nil
    self._txt_pressed = nil
    self._txt_disabled = nil
    
    self._state = State.Normal

    -- self:addNodeEventListener(cc.NODE_EVENT, function(event)
    --     if event.name == "enter" then
            
    --     end
    -- end)
end

function Button:setImage(normal, pressed, disabled)
    assert(normal ~= nil and normal ~= "")
    self._img_normal = display.newSprite(normal):addTo(self)
    
    if pressed ~= nil and pressed ~= "" then
        self._img_pressed = display.newSprite(pressed):addTo(self)
    else
        self._img_pressed = self._img_normal
    end
    
    if disabled ~= nil and disabled ~= "" then
        self._img_disabled = display.newSprite(disabled):addTo(self)
    else
        -- todo 使用shader变灰
        self._img_disabled = display.newSprite(normal):addTo(self)
    end
    
    self:updateImage()
    return self
end

function Button:updateImage()
    local state = self._state
    if state == State.Normal then
        if self._img_pressed then
            self._img_pressed:setVisible(false)
        end
        if self._img_disabled then
            self._img_disabled:setVisible(false)
        end
        
        if self._img_normal then
            self._img_normal:setVisible(true)
            self:setContentSize(self._img_normal:getContentSize())
            self._img_normal:setPosition(self:center())
        end
    end
end

function Button:changeState(state)
    self._state = state
    self:updateImage()
end

return Button
