
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

        local do_conn = function()
        	print("wow!!!!")
        end

        local gameManager = red.GameManager:getInstance()
        gameManager:init()
        --gameManager:connDelegate():bindConnect(do_conn)
        gameManager:start()

        local callback = function()
        	local protos = red.UIThreadTask:getInstance():pop_protos()

        	if #protos > 0 then
				print("recv proto...")
        	end

        	for k, v in pairs(protos) do
        		print(v["_proto_name_"])
        	end

        	red.UIThreadTask:getInstance():do_tasks()
        end

    cc.Director:getInstance():getScheduler():scheduleScriptFunc(callback, 0.5, false)
end

return MainScene
