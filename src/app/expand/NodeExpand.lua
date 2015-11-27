local Node = cc.Node

function Node:center()
	local size = self:getContentSize()
	return cc.p(size.width / 2, size.height / 2)
end