-- 测试用，无意义

local Notify = require("app.notify.NotifyManager").getInstance()
local binding = require("app.databinding.DataBinding")

local MyButton = class("Mybutton", cc.ui.UIPushButton)

function MyButton:ctor(images, options)
	MyButton.super.ctor(self, images, options)

	self:onButtonPressed(function(event)
        self:setScale(1.1)
    end)
    :onButtonRelease(function(event)
        self:setScale(1.0)
    end)
    :onButtonClicked(function(event)
        Notify:pub(self, "CLICK")
    end)

    self.Text = ""
    self.Text = binding.format(self.Text)

    local ui = self
    function self.Text:_valueChange_(value)
    	ui:setButtonLabel(cc.ui.UILabel.new({text = value}))
    end
end

return MyButton