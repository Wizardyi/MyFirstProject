local string=string
local string_format = string.format

_G.__importModule__ = _G.__importModule__ or {}
local __importModule__ = _G.__importModule__

local function doImport(pathFile)
	local new = {}
	setmetatable(new, {__index = _G})
	local func, err = loadfile(pathFile, "bt", new)
	if not func then
		print(string.format("ERROR!!!\n%s\n%s", err, debug.traceback()))
		return func, err
	end
	func()
	__importModule__[pathFile] = new
	new.__FILE__ = pathFile
	if new.__read_only__ then
		new.__read_only__()
	end
	if rawget(new, "__init__") then
		new:__init__()
	end
	return new
end

local function SafeImport(pathFile)
	local old = __importModule__[pathFile]
	if old then
		return old
	end
	return doImport(pathFile)
end

function Import(pathFile)
	local module, err = SafeImport(pathFile)
	assert(module, err)
	return module
end

local function getClassTbl(module)
	local classTbl = {}
	for k, v in pairs(module) do
		if type(v) == "table" and v.__IsClass then
			classTbl[k] = v
		end
	end
	return classTbl
end

local function refreshSubClassFunc(newClass, oldClassFunc, depth)
	assert(depth <= 20)
	for idx, subClass in pairs(newClass.__SubClass) do
		for k, v in pairs(newClass) do
			if type(v) == "function" then
				if not subClass[k] or (subClass[k] == oldClassFunc[k]) then
					subClass[k] = v
				end
			end
		end
		if subClass.__SubClass then
			refreshSubClassFunc(subClass, oldClassFunc, depth + 1)
		end
	end
end

local function updateImport(pathFile)
	local old = __importModule__[pathFile]
	if not old then
		return false
	end
	local oldClassTbl = getClassTbl(old)
	local oldModuleData = nil
	if old.saveDataOnUpdate then
		oldModuleData = old.saveDataOnUpdate()
	end
	local func, err = loadfile(pathFile, "bt", old)
	if not func then
		print(string.format("ERROR!!!\n%s\n%s", err, debug.traceback()))
		return false
	end
	func()
	local newClassTbl = getClassTbl(old)
	for newClassName, newClassIml in pairs(newClassTbl) do
		local oldClassIml = oldClassTbl[newClassName]
		if oldClassIml then
			local oldClassFunc = {}
			newClassTbl[newClassName] = oldClassIml
			for k, v in pairs(oldClassIml) do
				if type(v) == "function" then
					oldClassIml[k] = nil
					oldClassFunc[k] = v
				end
			end
			for k, v in pairs(newClassIml) do
				if type(v) == "function" then
					oldClassIml[k] = v
				end
			end
			if oldClassIml.__SubClass then
				refreshSubClassFunc(oldClassIml, oldClassFunc, 0)
			end
		end
	end
	for k, v in pairs(newClassTbl) do
		old[k] = v
	end
	if old.loadDataOnUpdate and oldModuleData then
		old.loadDataOnUpdate(oldModuleData)
	end
	if old.__read_only__ then
		old.__read_only__()
	end
	if rawget(old, "__init__") then
		old:__init__()
	end
	if rawget(old, "afterModuleUpdate") then
		old:afterModuleUpdate()
	end
	return true
end

function updateLuaFile(pathFile)
	local ret = updateImport(pathFile)
	return ret
end
