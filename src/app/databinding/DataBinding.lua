-- 数据绑定
-- 多对多的关系
-- 可以单向、双向、环形绑定
-- 需要自行避免重复绑定

local DataBinding = {}

function DataBinding.format(x)
	if type(x) ~= "table" or x["_DataBinding_"] == nil then
		x = {_value_ = x, _DataBinding_ = {}}
		function x:_valueChange_(value)
		end
	end
	return x
end

function DataBinding.check(x)
	if type(x) ~= "table" or x["_DataBinding_"] == nil then
		return false
	end
	return true
end

function DataBinding.bind(src, tar)
	src = DataBinding.format(src)
	tar = DataBinding.format(tar)
	local b_src = src["_DataBinding_"]
	b_src[#b_src+1] = tar
	return src, tar
end

function DataBinding.bindTwoWay(src, tar)
	src, tar = DataBinding.bind(src, tar)
	local b_tar = tar["_DataBinding_"]
	b_tar[#b_tar+1] = src
	return src, tar
end

function DataBinding.bindOneWay(...)
	local arg = {...}
	for i = 1, #arg-1 do
		arg[i], arg[i+1] = DataBinding.bind(arg[i], arg[i+1])
	end
	return unpack(arg)
end

function DataBinding.bindCircle(...)
	local arg = {...}
	for i = 1, #arg-1 do
		arg[i], arg[i+1] = DataBinding.bind(arg[i], arg[i+1])
	end
	arg[#arg], arg[1] = DataBinding.bind(arg[#arg], arg[1])
	return unpack(arg)
end

function DataBinding.set(x, value, hash)
	assert(DataBinding.check(x))
	hash = hash or {}
	hash[x] = true

	local filter = x["_filter_"]
	if filter then
		value = filter(x, value)
	end

	x["_value_"] = value
	x:_valueChange_(value)

	local arr = x["_DataBinding_"]
	for _, b in ipairs(arr) do
		if not hash[b] then
			DataBinding.set(b, value, hash)
		end
	end
end

function DataBinding.get(x)
	if DataBinding.check(x) then
		return x["_value_"]
	else
		return x
	end
end

return DataBinding