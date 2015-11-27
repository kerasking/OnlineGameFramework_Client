local scheduler = require("framework.scheduler")
local TestScene = require("app.scenes.TestScene")
local Notify = require("app.notify.NotifyManager").getInstance()
local binding = require("app.databinding.DataBinding")

local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    local btn = red.ui.Button.new()
        :setImage("Button01.png", "Button01.png", "Button01.png")
        :pos(300, 300)
        :addTo(self)
end

-- function MainScene:ctor()
--     cc.ui.UILabel.new({
--             UILabelType = 2, text = "Hello, World123", size = 64})
--         :align(display.CENTER, display.cx, display.cy)
--         :addTo(self)

--     self._btn = MyButton.new("Button01.png", {scale9 = true})
--         :setButtonSize(160, 80)
--         :setButtonLabel(cc.ui.UILabel.new({text = "Button"}))
--         :pos(display.cx - 300, display.bottom + 100)
--         :addTo(self)

--     Notify:sub(self._btn, "CLICK", self, function(recver, signal)
--         print("lambda " .. signal:name())
--     end)

--     Notify:sub(self._btn, "CLICK", self, self.hahaclick)


--     local str = ""
--     str = binding.bind(str, self._btn.Text)

--     function self._btn.Text:_filter_(value)
--         if #value <= 5 then
--             return value
--         else
--             return string.sub(value, 1, 5) .. "..."
--         end
--     end

--     Notify:sub(self._btn, "CLICK", self, function()
--         binding.set(str, binding.get(str) .. "A")
--         print("str:", binding.get(str))
--     end)
-- end

function MainScene:testDataBinding()
    local a = 111
    local b = 222
    local c = 333

    -- a, b = binding.bind(a, b)
    -- a, b = binding.bindTwoWay(a, b)
    -- a, b, c = binding.bindOneWay(a, b, c)
    -- a, b, c = binding.bindCircle(a, b, c)

    a, b = binding.bind(a, b)
    a, c = binding.bind(a, c)

    function a:_valueChange_(value)
        print("a change", value)
    end

    function b:_valueChange_(value)
        print("b change", value)
    end

    function c:_valueChange_(value)
        print("c change", value)
    end

    function c:_filter_(value)
        return value / 10
    end

    binding.set(a, 200)
    -- db.set(a, 300)
    print(binding.get(a), binding.get(b), binding.get(c))
end

function MainScene:hahaclick(signal)
    print("成员函数 " .. signal:name())
end

function MainScene:onEnter()
    -- Notify:rmReceiver(self)
    -- self._btn:removeSelf()


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
