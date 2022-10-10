#!/usr/bin/lua
local string_format = string.format
local table_insert = table.insert

inputTbl = {}

function addInput(a)
	table_insert(inputTbl, a)
	printTbl()
end

function printTbl()
	for k, v in pairs(inputTbl) do
		print(k, v)
	end
end

function saveDataOnUpdate()
	local tbl = {}
	tbl.inputTbl = inputTbl
	return tbl
end

function loadDataOnUpdate(data)
	inputTbl = data.inputTbl
end

function __init__()
	print("test2 init")
end

