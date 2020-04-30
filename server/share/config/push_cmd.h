#ifndef	SHARE_PUSH_H
#define SHARE_PUSH_H
#include "NetMsg.pb.h"

enum PushOperation{
	PushOperation_Invalid               = 0,  // 无效类型
	PushOperation_SingleDeviceAndroid   = 1,  // 推送单个设备 android设备使用
	PushOperation_SingleDeviceIos       = 2,  // 推送单个设备，ios设备使用
	PushOperation_SingleAccountAndroid  = 3,  // 推送单个账号，android设备使用
	PushOperation_SingleAccountIos      = 4,  // 推送单个账号，ios设备使用
	PushOperation_AccountListAndroid        = 5,  // 推送账号列表，android设备使用
	PushOperation_AccountListIos            = 6,  // 推送账号列表，ios设备使用
	PushOperation_AllDeviceAndroid      = 7,  // 推送全部设备，android设备使用
	PushOperation_AllDeviceIos          = 8,  // 推送全部设备，ios设备使用
	PushOperation_TagsAndroid           = 9,  // 推送标签，android设备使用
	PushOperation_TagsIos               = 10, // 推送标签，ios设备使用
	PushOperation_CreateMultipAndroid   = 11, // 创建批量推送消息
	PushOperation_CreateMultiIos            = 12, // 创建批量推送消息
	PushOperation_AccountListMultiple   = 13, // 推送消息给大批量账号
	PushOperation_DeviceListMultiple        = 14, // 推送消息给大批量设备
	PushOperation_QueryStatus           = 15, // 查询群发消息状态
	PushOperation_QueryDeviceCount      = 16, // 查询消息覆盖的设备数
	PushOperation_QueryTags             = 17, // 查询应用当前所有的tags
	PushOperation_QueryTagToken         = 18, // 查询带有指定token的设备
	PushOperation_QueryTag              = 19, // 查询设备下所有的tag 
	PushOperation_CancelTiming          = 20, // 取消尚未推送的定时任务
	PushOperation_BatchSetTag           = 21, // 批量为token设置标签
	PushOperation_BatchDelTag           = 22, // 批量为token删除标签
	PushOperation_QueryInfoOfToken      = 23, // 查询token相关的信息，包括最近一次活跃时间，离线消息数等
	PushOperation_QueryTokensOfAccount  = 24, // 查询账号绑定的token
	PushOperation_DeleteTokenOfAccount  = 25, // 删除指定账号和token的绑定关系（token仍然有效）
	PushOperation_DeleteAllTokensOfAccount  = 26 // 删除指定账号绑定的所有token（token仍然有效）
};      

//NetMsg::PushStyle* GetDefaultStyle();

#endif
