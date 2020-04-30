#ifndef __SIZE_H_
#define __SIZE_H_

// 通信缓存长度定义
#define OL_TO_SVR_LEN (100*1024)			// online 发往其他服务器的缓存大小
#define CLI_PROTO_MAX_LEN (16*1024)		// client 发送给 online 协议包最大长度（框架缓存区 3200K）
#define OL_TO_CLI_MAX_LEN (1024*1024)	// online 发送给 cli 协议包最大长度
#define SVR_TO_OL_MAX_LEN (3200*1024)	// 其他服务器发往 online 的协议长度

#define CACHE_PROTO_SIZE (30)	// 玩家最多缓存协议条数
#define NICK_NAME_LEN 50 				// 玩家昵称

enum {
	COMMON_SOLDIER_HEALTH			= 60,	// 1 个兵力占 60 个血量
};

// #define GREETING_LEN  200 				// 玩家问候语
// #define MAX_ROOM_NUM 6 					// 每个房子含有的房间数量
// #define MAIL_TITLE_LEN 50				// 邮件标题长度上限
// #define MAIL_CONTENT_LEN 610    		// 邮件内容长度上限
// #define CHAT_TIMES_MAX 10				// 普通玩家每日聊天上限
// #define CHAT_TIME_VIP_MAX 20			// VIP玩家每日聊天上限
// #define DAILY_GET_MAIL_POWER_LIMIT 50	// 每天从邮件中获得体力上限
// #define HOME_MAX_PLAYER_NUM 20 			// 小屋能容纳最大的人数
// #define SCENE_MAX_PLAYERE_NUM 20 		// 每个公共场景副本能容纳的最大的人数
// #define SCENE_MAX_NUM 10000 			// 场景最多建立的副本数
// #define CHANGE_NICK_COST 50 			// 改昵称花费
// #define CP_ROOM_ID 1000					// cp 房间id
// #define CHAT_LEN (40*3)					// 每次聊天最大长度
// #define ROOM_NAME_LEN (50)				// 房间名称最大长度
// #define SUB_CLOTH_SCORE (0.3)			// 衣服减分系数
#define SOURCE_NUM_LEN (256)			// 渠道账号长度
#define DEVICE_LEN (128)				// 设备号长度
#define LANGUAGE_LEN (128)				// 系统语言长度
#define DEVICE_TYPE_LEN (128)			// 设备类型长度
#define MEDIA_SOURCE_LEN (128)			// 韩国需求
#define CAMPAIGN_LEN (128)				// 韩国需求
#define LEGION_INVASION_TEAM (100)		// 南蛮入侵每个入侵点最多同时存在的部队数量
										// 边防军最多拉取到的部队数量

// #define MAX_CONTENT_LEN 2000			// 消息最大长度
// #define MONTH_CARD_NEED_RMB 30			// 充值月卡需要的RMB
// #define WISH_CONTENT_MAX_LEN 512		// 心愿最大值
// #define INIT_HOME_POPULARITY 0			// 默认初始化点赞数量
// #define INIT_MONEY 50000				// 默认初始化金币数量
// #define INIT_DIAMOND 100				// 默认初始化赠送钻石数量
// #define INIT_TOTAL_DIAMOND 0			// 默认初始化充值钻石数量（用于设置vip至6级）
// #define INIT_FLOWER_FOOD 0				// 默认初始化花养料数量
// #define INIT_TREASURE_HUNT_TIMES (5)	// 每日寻宝次数
// 
// #define NEWPLAYER_THRESHHOLD (12)       //NEWPLAYER大于等于12时,新手阶段结束cb_20160425
// #define MAX_SKILL (10)                  //技能总数
// 
// #define INIT_HOME_POPULARITY 0			// 默认初始化点赞数量
// #define RANK_TIME (2000000000)			// reids 排行榜高32位值由该值减去分数获取当前时间戳
// 										// 以期获得一个时间戳权重保证相同分数越早得到排名越前
// 										// 客户端从服务器获取的分数应该只显示低32位
// 										// 该时间为 2033/5/18 11:33:20 如果项目有幸运营到这个时间点，该值需要扩大
// 										// （废弃，策划说了，越晚提交的分数，相同排名需要排前面）

#define DAY_START_TIME (5)				// 当天每日数据将在第二天凌晨5点清理
#define DAY_SECS (86400)				// 定义一天多少秒，正常是 86400
#define DAY_ARENA_TIMES_MAX (5)			// 竞技场每日次数初始化最多5次
#define DAY_CHALLENGE_TIMES_MAX (5)		// 名将挑战每次次数初始化最多5次

#define CHALLENGE_PROP_REDUCE_LEVEL (5)	// 名将挑战道具降低等级数

#define SKILL_CHANGE_ITEM_VALUE (10000) // 技能id转换itemid值

#define RELOAD_TIME (10)		//检查重新加载时间间隔

#define CONFIG_DATAID_MIN	(10000000) //放数据库的配置最小id

#define CONFIG_DATAID(dataid) (dataid >= 10000000)		//是否是放数据库的配置最小id

// 墨三国
// 每个 online 可以容纳的玩家人数
#define ONLINE_MAX_USER_NUM (300)
#define FRIEND_REQUEST_MAX_COUNT (30)		// 每个玩家每日可以申请的好友数量上限
#define FRIEND_REQUEST_LIST_MAX_COUNT (100) // 每个玩家自己的好友申请队列数量上限

// enum USER_INFO_FIELD {
// 	VIRTUAL_TOTAL_DIAMOND 			= 300000, 			// 充值总钻石数
// 	VIRTUAL_TITLE 					= 300001, 			// 称号
// 	VIRTUAL_BIRTHDAY                = 300002,           // 生日、星座
// 	VIRTUAL_CONSORTIA               = 300003, 			// 公会
// 	VIRTUAL_GREETING	 			= 300004, 			// 问候语
// 	VIRTUAL_NICK	       			= 300005, 			// 昵称
// 	VIRTUAL_STEWARD_NICK	        = 300006, 			// 管家昵称
// 	VIRTUAL_LAST_LOGIN_TM			= 300007,			// 最近一次登录的时间戳
// 	VIRTUAL_POPULARITY				= 300008,			// 人气值
// 	VIRTUAL_PLANT_POT				= 300009,			// 庭院种植数
// 
// 	VIRTUAL_ITEM_POWER              = 400001,			// 体力
// 	VIRTUAL_ITEM_MONEY              = 400002,			// 金币
// 	VIRTUAL_ITEM_DIAMOND            = 400003,			// 钻石
// 	VIRTUAL_ITEM_LEVEL              = 400005,           // 玩家等级（不能通过 add_items 和 del_items 操作）
// 	VIRTUAL_ITEM_CP_LEVEL           = 400006,           // CP 好感度等级（不能通过 add_items 和 del_items 操作）
// 	VIRTUAL_ITEM_FLOWER_FOOD        = 400007, 			// 花房养料
// 	VIRTUAL_ITEM_EXP				= 400008,			// 经验
// 	VIRTUAL_ITEM_CP_INTIMADY		= 400009,			// cp 亲密度
// 
// 	VIRTUAL_ITEM_CRISTAL            = 500001,			// 水晶(竞技场代币)
// };

enum ITEM_SOURCE {
	SOURCE_NORMAL                   = 10000,			// 普通
	SOURCE_IOS_IAP                  = 10001,			// IOS_IAP 购买
	SOURCE_SHOPPING                 = 10002,			// 商城 购买
	SOURCE_GASHAPON                 = 10003,            // 扭蛋 购买
    SOURCE_REWARD                   = 10004,            // 奖励
    SOURCE_TASK                     = 10005,            // 做任务
    SOURCE_BATTLE                   = 10006,            // 挑战
    //虚拟货币
    FREE_GET_MONEY                  = 10007,             //免费获得金币 
    RECHARGE_GET_MONEY              = 10008,             //充值获得金币
    CONSUME_MONEY                   = 10009,             //消耗金币

};

enum mail_type {
    MAIL_TYPE_SYS = 0,
    MAIL_TYPE_USER = 1,
	MAIL_TYPE_POWER = 2,
};

enum cp_common_data_t
{
    REQ_TIME_LIMIT = 7 * 86400,
};

enum GET_INFO_TYPE
{
	GET_INFO_COURTYARD = 12,
};

enum ACCOUNT_SOURCE
{
	SOURCE_IOS_APPSTORE			= 1,				// 苹果商店
	SOURCE_IOS_JAILBREAK			= 2,				// 苹果越狱
	SOURCE_ANDROID_YINGYONGBAO	= 3,				// 应用宝
	SOURCE_ANDROID_MHA			= 4,				// 硬核联盟
	SOURCE_ANDROID_MIX			= 5,				// 安卓混服
	SOURCE_MAX,										// 渠道总数
};

enum ACCOUNT_PLATFORM
{
	PLATFORM_TEST                                   = 0,    // 测试账号
	PLATFORM_TAOMEE					                = 1,    // 淘米账号
	PLATFORM_XYZS						            = 2,    // XY 苹果助手
	PLATFORM_IOS_APPSTORE				            = 101,  // 苹果商店
	PLATFORM_IOS_JINYOU				                = 102,  // 锦游iOS
	PLATFORM_IOS_QIYU				                = 103,  // 奇遇iOS
	PLATFORM_IOS_JAILBREAK			                = 201,  // 苹果越狱
	PLATFORM_ANDROID_FEILIU			                = 501,  // 飞流
	PLATFORM_ANDROID_UC				                = 502,  // UC
	PLATFORM_ANDROID_360				            = 503,  // 360
	PLATFORM_ANDROID_BAIDU			                = 504,  // 百度
	PLATFORM_ANDROID_DANGLE			                = 505,  // 当乐
	PLATFORM_ANDROID_XIAOMI			                = 506,  // 小米
	PLATFORM_ANDROID_YINGYONGBAO		            = 507,  // 应用宝
	PLATFORM_ANDROID_4399			                = 508,  // 4399
	PLATFORM_ANDROID_HUAWEI			                = 509,  // 华为
	PLATFORM_ANDROID_VIVO				            = 510,  // Vivo
	PLATFORM_ANDROID_OPPO				            = 511,  // Oppo
	PLATFORM_ANDROID_LENOVO			                = 512,  // 联想
	PLATFORM_ANDROID_COOLPAD			            = 513,  // 酷派
	PLATFORM_ANDROID_MEIZU			                = 514,  // 魅族
	PLATFORM_ANDROID_GIONEE			                = 515,  // 金立
	PLATFORM_ANDROID_TT			                    = 516,  // tt语音
	PLATFORM_ANDROID_YIWAN			                = 517,  // 益玩
	PLATFORM_ANDROID_NUBIA			                = 518,  // nubia
	PLATFORM_ANDROID_XIAO7			                = 519,  // 小7
	PLATFORM_ANDROID_KAOPU			                = 520,  // 靠谱
	PLATFORM_ANDROID_YAOWANG		                = 521,  // 遥望
	PLATFORM_ANDROID_PAPAYOUXI		                = 522,  // 啪啪游戏厅
	PLATFORM_ANDROID_PPTV			                = 523,  // PPTV
	PLATFORM_ANDROID_GUOPAN							= 524,  // 果盘
	PLATFORM_ANDROID_SHENGUI		                = 525,  // 神鬼(feiliu)
	PLATFORM_ANDROID_AOSHI			                = 526,  // 傲视(feiliu)
	PLATFORM_ANDROID_SAMSUNG		                = 527,  // 三星
	PLATFORM_ANDROID_PANDA_WAN		                = 528,  // 熊猫玩
	PLATFORM_ANDROID_YUEYOU			                = 529,  // 悦游
	PLATFORM_ANDROID_QIYU			                = 530,  // 奇遇
	PLATFORM_ANDROID_JINYOU_SANGUOZHI	            = 531,  // 锦游三国志
	PLATFORM_ANDROID_QIYU_LUANSHI		            = 532,  // 奇遇我主乱世
	PLATFORM_ANDROID_QIYU_WANGCHAO		            = 533,  // 奇遇九州王朝
    PLATFORM_ANDROID_JINYOU_GUANGDIANTONG           = 535,  // 锦游广点通
    PLATFORM_IOS_HUIYAO                             = 536,  // 辉耀iOS
    PLATFORM_ANDROID_HUIYAO                         = 537,  // 辉耀Android
    PLATFORM_IOS_HUANYU                             = 550,  // 欢娱iOS
    PLATFORM_ANDROID_HUANYU                         = 551,  // 欢娱Android
    PLATFORM_IOS_YJM                                = 571,  // 韩国YJM iOS
    PLATFORM_ANDROID_YJM                            = 572,  // 韩国YJM Android
    PLATFORM_ONESTORE_YJM                           = 573,  // 韩国ONESTORE YJM
    PLATFORM_SAMSUNG_YJM                            = 574,  // 韩国三星 YJM
    PLATFORM_GAMOTA                                 = 581,  // 越南Gamota
    PLATFORM_IOS_QIANGWAN                           = 590,  // 抢玩iOS
    PLATFORM_ANDROID_QIANGWAN                       = 591,  // 抢玩Android
    PLATFORM_IOS_DIANHUN							= 592,  // 电魂IOS
    PLATFORM_ANDROID_DIANHUN						= 593,  // 电魂Android
    PLATFORM_IOS_JIUSOU								= 594,  // 九搜绝地三国IOS
    PLATFORM_IOS_JIUSOU_CEYU						= 595,  // 九搜策驭三国IOS
    PLATFORM_IOS_6KW								= 596,  // 6kw聚合IOS
    PLATFORM_ANDROID_6KW							= 597,  // 6kw聚合Android
	PLATFORM_IOS_DIANHUN_LYSQ						= 598,  // 电魂狼烟四起IOS
	PLATFORM_ANDROID_DIANHUN_LYSQ					= 599,  // 电魂狼烟四起Android
	PLATFORM_IOS_YITONGSANGUO						= 600,  // 一统三国iOS
	PLATFORM_IOS_WENDINGSANGUO						= 601,  // 问鼎三国iOS
	PLATFORM_ANDROID_TAIYOU							= 602,  // 台游Android
	PLATFORM_IOS_TAIYOU								= 603,  // 台游IOS
	PLATFORM_ANDROID_TAIYOU_OFFICIAL				= 604,  // 台游Android(官方)
	PLATFORM_IOS_JUNXIN								= 607,  // 俊欣IOS
	PLATFORM_IOS_WANDE6								= 608,  // 玩的溜IOS
	PLATFORM_IOS_YOUDONG							= 609,	//游动ios
	PLATFORM_MAX,								            // 平台总数
};

enum Language{
	Simplified_Chinese		= 0,	// 简体中文
	Traditional_Chinese		= 1,	// 繁体中文
	Korean					= 2,	// 韩文
	English					= 3,	// 英文
	Japanese				= 4,	// 日文
	Vietnamese				= 5,	// 越南文
};

enum GmSetUserMdmType{
	GmSetUserMdmType_UserInfo	= 0,  // 用户信息
	GmSetUserMdmType_Hero		= 1,  // 武将
	GmSetUserMdmType_Item		= 2,  // 道具
	GmSetUserMdmType_Quset		= 3,  // 任务
	GmSetUserMdmType_Cycle		= 4,  // 强兵
	GmSetUserMdmType_Biography	= 5,  // 列传
	GmSetUserMdmType_Mail		= 6,  // 邮件
};

enum GmSetUserInfo{
	GmSetUserInfo_Name			= 0,  // 用户名
	GmSetUserInfo_Online		= 1,  // 在线情况
	GmSetUserInfo_Level			= 2,  // 等级
	GmSetUserInfo_Exp			= 3,  // 经验
	GmSetUserInfo_Rank			= 4,  // 官品
	GmSetUserInfo_ForceCity		= 5,  // 势力城池
	GmSetUserInfo_City			= 6,  // 城池
	GmSetUserInfo_Contribution	= 7,  // 贡献
	GmSetUserInfo_Exploit		= 8,  // 战功
	GmSetUserInfo_Reputation	= 9,  // 声望
	GmSetUserInfo_pvpMedal		= 10, // 武勋
	GmSetUserInfo_Gold			= 11, // 元宝
	GmSetUserInfo_BindGold		= 12, // 绑定元宝
	GmSetUserInfo_Coin			= 13, // 铜钱
	GmSetUserInfo_SoulStone		= 14, // 魂石
	GmSetUserInfo_Stone			= 15, // 石料
	GmSetUserInfo_Iron			= 16, // 铁矿
	GmSetUserInfo_Wood			= 17, // 木材
	GmSetUserInfo_Stamina		= 18, // 粮草
	GmSetUserInfo_GeneralSoul	= 19, // 将魂
	GmSetUserInfo_HeroFriendShip = 20, // 武将好感度
	GmSetUserInfo_Atlas			= 21, // 图鉴
	GmSetUserInfo_WeekCard		= 22, // 周卡
	GmSetUserInfo_MoonCard		= 23, // 月卡
	GmSetUserInfo_StopMove		= 24, // 停止移动
	GmSetUserInfo_GuildTech		= 25, // 军团科技
	GmSetUserInfo_NewGuid		= 26, // 设置引导
};

enum GmSetHeroInfo{
	GmSetHeroInfo_Level			= 0,  // 等级
	GmSetHeroInfo_Strength		= 1,  // 武力值
	GmSetHeroInfo_Wisdom		= 2,  // 智谋
	GmSetHeroInfo_Luck			= 3,  // 幸运
	GmSetHeroInfo_Charm			= 4,  // 魅力
	GmSetHeroInfo_Leadership	= 5,  // 统帅
	GmSetHeroInfo_CDTime		= 6,  // CD冷却
	GmSetHeroInfo_Delete		= 7,  // 删除
	GmSetHeroInfo_SkillLevel	= 8,  // 技能等级
	GmSetHeroInfo_NewAdvCD		= 9,  // 奇遇CD
};

enum GmSetQusetInfo{
	GmSetQusetInfo_Chapter		= 0,  // 章节任务
	GmSetQusetInfo_Country		= 1,  // 国家任务
	GmSetQusetInfo_NewAdv		= 2,  // 奇遇任务
};

enum GmSetBioInfo{
	GmSetBioInfo_Hero			= 0,  // 武将列传
	GmSetBioInfo_Country		= 1,  // 国家列传
};
#endif
