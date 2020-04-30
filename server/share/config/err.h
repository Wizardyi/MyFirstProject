#pragma once

// 编码定义规范
// 1、每个服务产生的错误码严格规定在相应的段内
// 2、错误码定义 服务简写_err_xxxx （比如：db_err_cmd_not_found 该协议在 db 服务上未实现）
// 3、错误码严格上顺序定义，不要随意跳过，如果定义了一个范围，需要写明上限和下限
// 错误码的定义从 20000 起
// 20000-20999  db 以及 dbproxy 产生的错误码
// 21000-21999	cache 产生的错误码 
// 22000-22999	position 产生的错误码
// 23000-23999	switch 产生的错误码
// 24000-24999	world 产生的错误码
// 25000-25999	login 产生的错误码
// 26000-26999	online 产生的错误码
// 27000-27999	gate 产生的错误码
// 28000-28999	battle 产生的错误码
// 29000-29999

enum errno_t {
	db_err_cmd_not_found		= 20000, // 该协议在 db 服务上未实现

	cache_err_cmd_not_found		= 21000, // 该协议在 cache 服务上未实现
	
	position_err_cmd_not_found	= 22000, // 该协议在 position 服务上未实现
	position_err_proto_format	= 22001, // position 协议解析错误

	switch_err_cmd_not_found		= 23000, // 该协议在 switch 服务上未实现
	switch_err_sys_err				= 23001, // 系统错误	
	switch_err_online_not_exist 	= 23002, // online不存在
	switch_err_proto_format			= 23003, // 协议格式错误
	switch_err_online_id_beyond_max = 23004, // onlineID超过了最大数
	switch_err_player_not_login		= 23005, // 玩家不在线

	world_err_cmd_not_found		= 24000, // 该协议在 world 服务上未实现

	login_err_cmd_not_found				= 25000, // 该协议在 login 服务上未实现
	login_err_sys_err					= 25001, // 系统错误 
	login_err_sys_busy					= 25002, // 系统繁忙
	login_err_proto_format				= 25003, // 协议格式错误
	login_err_source_not_exit			= 25004, // 区号不存在
	login_err_multi_primary_key			= 25005, // 多个 key 值，账号验证超时
	login_err_invalid_session			= 25006, // 无效的 session
	login_err_invalid_param				= 25007, // 无效的参数
	login_err_invalid_service			= 25008, // 无效的 service
	login_err_source_not_be_activate	= 25009, // 区号未生效

	online_err_cmd_not_found			= 26000, // 该协议在 oline 服务上未实现
	online_err_player_not_login			= 26001, // player 未在 online 登录，请先登录
	online_err_player_already_login		= 26002, // player 已经 online 登录，请勿重复登录
	online_err_player_is_busy			= 26003, // 玩家协议处理繁忙
	online_err_proto_format				= 26004, // online 协议解析错误
	online_err_create_player			= 26005, // online 分配玩家对象失败，详情查看服务器错误日志

	gate_err_cmd_not_found		= 27000, // 该协议在 gate 服务上未实现
	gate_err_proto_format		= 27001, // gate 协议解析错误
	gate_err_create_player		= 27002, // online 分配玩家对象失败，详情查看服务器错误日志

	battle_err_cmd_not_found	= 28000, // 该协议在 battle 服务上未实现
};

