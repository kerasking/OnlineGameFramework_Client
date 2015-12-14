local Node = cc.Node

function Node:center()
	local size = self:getContentSize()
	return cc.p(size.width / 2, size.height / 2)
end

function Node:checkTouch(x, y)
	local point
	if y == nil then
		point = x
	else
		point = cc.p(x, y)
	end
	return self:getCascadeBoundingBox():containsPoint(point)
end

-- 修改Node的构造函数
-- local ctor_old = Node.create
-- function Node:create()
-- 	ctor_old(Node)
-- 	print("[Red] Node create...")
-- end