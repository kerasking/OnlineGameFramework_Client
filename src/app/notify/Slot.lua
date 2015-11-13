local Slot = class("Slot")

function Slot:ctor(receiver, func)
	self._receiver = receiver
	self._func = func
end

function Slot:receiver()
	return self._receiver
end

function Slot:call(...)
	self._func(self._receiver, ...)
end

return Slot