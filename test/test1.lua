#!/usr/bin/lua
local string_format = string.format
local table_insert = table.insert

local TEST2 = Import("test2.lua")

function loop()
	while true do
		print("input a:")
		local a = io.read()
		if a == "exit" then
			break
		end
		if a == "1" then
			updateLuaFile("test2.lua")
		end
		TEST2.addInput(a)
		print(#TEST2.inputTbl)
	end
end

function __init__()
	print("test1 init")
end

