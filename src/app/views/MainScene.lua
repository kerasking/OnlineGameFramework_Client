
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

function MainScene:onCreate()
    -- add background image
    display.newSprite("HelloWorld.png")
        :move(display.center)
        :addTo(self)

    -- add HelloWorld label
    cc.Label:createWithSystemFont("Hello World", "Arial", 40)
        :move(display.cx, display.cy + 200)
        :addTo(self)


        local uiTask = function()
            red.UIThreadTask:getInstance():do_tasks()
            local protos = red.UIThreadTask:getInstance():pop_protos()

            if #protos > 0 then
                print("recv proto...")
            end

            for k, v in pairs(protos) do
                print(v["_proto_name_"])
            end
        end

        local do_conn = function(event)
            print("[Red] connected!!!")
            cc.Director:getInstance():getScheduler():scheduleScriptFunc(uiTask, 0.5, false)
        end

        local do_disconn = function(event)
            print("[Red] disconnect!!!")
            cc.Director:getInstance():getScheduler().unscheduleGlobal(uiTask)
            --red.GameManager:getInstance():stop() 现在由c++负责停止
        end

        local do_connerr = function(event)
            print("[Red] connect error")
            --cc.Director:getInstance():getScheduler().unscheduleScriptFunc(uiTask)
        end

        local dispatcher = cc.Director:getInstance():getEventDispatcher();
        dispatcher:addEventListenerWithFixedPriority(cc.EventListenerCustom:create("CONNECT", do_conn), 1);
        dispatcher:addEventListenerWithFixedPriority(cc.EventListenerCustom:create("DISCONNECT", do_disconn), 1);
        dispatcher:addEventListenerWithFixedPriority(cc.EventListenerCustom:create("CONNECT_ERROR", do_connerr), 1);

        local gameManager = red.GameManager:getInstance()
        gameManager:init()
        gameManager:start()
end

function MainScene:TMP()
    print("[Red] XXXXXXXXXXXXXX")
end

return MainScene
