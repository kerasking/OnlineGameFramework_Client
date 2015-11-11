
local TestScene = class("TestScene", function()
    return display.newScene()
end)

function TestScene:ctor()
    -- add background image
    display.newSprite("HelloWorld.png")
        :move(display.center)
        :addTo(self)

    -- add HelloWorld label
    cc.Label:createWithSystemFont("TestScene", "Arial", 40)
        :move(display.cx, display.cy + 200)
        :addTo(self)

        local do_disconn = function(event)
            print("[Red] disconnect TestScene")
            cc.Director:getInstance():getScheduler().unscheduleGlobal(uiTask)
            --red.GameManager:getInstance():stop() 现在由c++负责停止
        end

        local do_connerr = function(event)
            print("[Red] connect error TestScene")
            --cc.Director:getInstance():getScheduler().unscheduleScriptFunc(uiTask)
        end

        local dispatcher = cc.Director:getInstance():getEventDispatcher();
        dispatcher:addEventListenerWithFixedPriority(cc.EventListenerCustom:create("DISCONNECT", do_disconn), 1);
        dispatcher:addEventListenerWithFixedPriority(cc.EventListenerCustom:create("CONNECT_ERROR", do_connerr), 1);
end

return TestScene
