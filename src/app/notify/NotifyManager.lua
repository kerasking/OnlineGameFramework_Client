local Signal = require("app.notify.Signal")
local Slot = require("app.notify.Slot")
local NotifyManager = class("NotifyManager")

function NotifyManager.getInstance()
	if NotifyManager._instance == nil then
		NotifyManager._instance = NotifyManager.new()
	end
	return NotifyManager._instance
end

function NotifyManager:ctor()
	self._signalpool = {}
end

function NotifyManager:sub(sender, signalName, receiver, slotFunc)
	local pool = self._signalpool

	local signals = pool[sender]
	if signals == nil then
		pool[sender] = {}
		signals = pool[sender]
	end

	local signal = signals[signalName]
	if signal == nil then
		signals[signalName] = Signal.new(sender, signalName)
		signal = signals[signalName]
	end

	signal:sub(Slot.new(receiver, slotFunc))
end

function NotifyManager:pub(sender, signalName)
	local pool = self._signalpool

	local signals = pool[sender]
	if signals == nil then
		return
	end

	local signal = pool[sender][signalName]
	if signal == nil then
		return
	end

	signal:pub()
end

-- 删除sender时，订阅此sender任何事件的所有slot都会移除
function NotifyManager:rmSender(sender)
	self._signalpool[sender] = nil
end

-- 删除receiver时，receiver中所有的slot都会移除
function NotifyManager:rmReceiver(receiver)
	-- 这个目前实现不够理想，需要遍历所有signal，删除其中的receiver
	local pool = self._signalpool
	for _, signals in pairs(pool) do
		for _, signal in pairs(signals) do
			signal:rmReceiver(receiver)
		end
	end
end

return NotifyManager