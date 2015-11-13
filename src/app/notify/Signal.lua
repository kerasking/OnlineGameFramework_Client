local Signal = class("Signal")

function Signal:ctor(sender, signalName)
	self._sender = sender
	self._name = signalName
	self._slots = {}
end

function Signal:equals(other)
	return self._sender == other._sender and 
			self._signalName == other._signalName
end

function Signal:sender()
	return self._sender
end

function Signal:name()
	return self._name
end

function Signal:sub(slot)
	local slots = self._slots
	slots[#slots+1] = slot
end

function Signal:pub()
	local slots = self._slots
	for _, v in ipairs(slots) do
		v:call(self)
	end
end

function Signal:rmReceiver(receiver)
	local slots = self._slots
	local i = 1
	while i <= #slots do
		local slot = slots[i]
		if slot:receiver() == receiver then
			table.remove(slots, i)
		else
			i = i + 1
		end
	end
end

return Signal