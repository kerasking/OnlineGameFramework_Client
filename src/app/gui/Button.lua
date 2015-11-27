local Widget = require("app.gui.Widget")
local Notify = require("app.notify.NotifyManager").getInstance()

local Button = class("Button", Widget)

Button.State = {
    Normal = 0,
    Pressed = 1,
    Disabled = 2
}

local State = Button.State

function Button:ctor()
    Button.super.ctor(self)

    self:setTouchEnabled(true)
    self:addNodeEventListener(cc.NODE_TOUCH_EVENT, handler(self, self.onTouchEvent))

    self._img_normal = nil
    self._img_pressed = nil
    self._img_disabled = nil

    self._txt_normal = nil
    self._txt_pressed = nil
    self._txt_disabled = nil
    
    self._state = State.Normal
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

function Button:setState(state)
    if self._state ~= state then
        self._state = state
        self:updateImage()
    end
    return self
end

function Button:updateImage()
    local state = self._state
    if self._img_normal == nil then
        return
    end 

    local img_cur
    if state == State.Normal then
        self._img_pressed:setVisible(false)
        self._img_disabled:setVisible(false)
        img_cur = self._img_normal
    elseif state == State.Pressed then
        self._img_normal:setVisible(false)
        self._img_disabled:setVisible(false)
        img_cur = self._img_pressed
    else
        self._img_normal:setVisible(false)
        self._img_pressed:setVisible(false)
        img_cur = self._img_disabled
    end
    img_cur:setVisible(true)
    self:setContentSize(img_cur:getContentSize())
    img_cur:setPosition(self:center())
end

function Button:onTouchEvent(event)
    if self._state == State.Disabled then
        return false
    end
    
    local name, x, y = event.name, event.x, event.y
    
    if name == "began" then
        self.touchBeganX = x
        self.touchBeganY = y
        if not self:checkTouch(x, y) then
            self:setState(State.Normal)
            return false
        end
        self:setState(State.Pressed)
        return true
    end

    local touchIn = self:checkTouch(x, y)
    
    if name == "moved" then    
        if touchIn then
            self:setState(State.Pressed)
        else
            self:setState(State.Normal)
        end
    end

    if name == "ended" then
        self:setState(State.Normal)
        if touchIn then
            Notify:pub(self, "Click")
        end
    end
end

return Button
