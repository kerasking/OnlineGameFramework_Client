local scheduler = require("framework.scheduler")
local TestScene = require("app.scenes.TestScene")
local Notify = require("app.notify.NotifyManager").getInstance()

local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    cc.ui.UILabel.new({
            UILabelType = 2, text = "Hello, World123", size = 64})
        :align(display.CENTER, display.cx, display.cy)
        :addTo(self)

    self._btn = cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonSize(160, 80)
        :setButtonLabel(cc.ui.UILabel.new({text = "Button"}))
        :onButtonPressed(function(event)
            event.target:setScale(1.1)
        end)
        :onButtonRelease(function(event)
            event.target:setScale(1.0)
        end)
        :onButtonClicked(function(event)
            NotifyManager:pub(event.target, "CLICK")
        end)
        :pos(display.cx - 300, display.bottom + 100)
        :addTo(self)

    Notify:sub(self._btn, "CLICK", self, function(recver, signal)
        print("lambda " .. signal:name())
    end)

    Notify:sub(self._btn, "CLICK", self, self.hahaclick)
end

function MainScene:hahaclick(signal)
    print("成员函数 " .. signal:name())
end

function MainScene:onEnter()
    


	-- local uiTask = function()
 --        red.UIThreadTask:getInstance():do_tasks()
 --        local protos = red.UIThreadTask:getInstance():pop_protos()

 --        if #protos > 0 then
 --            print("recv proto...")
 --        end

 --        for k, v in pairs(protos) do
 --            print(v["_proto_name_"])
 --        end
 --    end

 --    local do_conn = function(event)
 --        print("[Red] connected!!!")
 --        scheduler.scheduleUpdateGlobal(uiTask)

	-- 	local scene = TestScene.new()
	-- 	display.replaceScene(scene)
 --    end

 --    local do_disconn = function(event)
 --        print("[Red] disconnect!!!")
 --    end

 --    local do_connerr = function(event)
 --        print("[Red] connect error")
 --    end

 --    local dispatcher = cc.Director:getInstance():getEventDispatcher();
 --    dispatcher:addEventListenerWithFixedPriority(cc.EventListenerCustom:create("CONNECT", do_conn), 1);
 --    dispatcher:addEventListenerWithFixedPriority(cc.EventListenerCustom:create("DISCONNECT", do_disconn), 1);
 --    dispatcher:addEventListenerWithFixedPriority(cc.EventListenerCustom:create("CONNECT_ERROR", do_connerr), 1);

 --    local gameManager = red.GameManager:getInstance()
 --    gameManager:init()
 --    gameManager:start()
end

function MainScene:onExit()
end

return MainScene
