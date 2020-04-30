#pragma once 
#include <deque> 
#include <map> 
#include "google/protobuf/repeated_field.h"
#include "NetMsg.pb.h"
#include "share/module/singleton.h"


class CChatRecordMgr : public Singleton<CChatRecordMgr>
{
public:
	CChatRecordMgr();
	~CChatRecordMgr();

	/*
	* 保存玩家聊天记录
	* param
	* id：玩家ID
	* info：聊天记录
	*/
	void addUserOfflineMsg(uint32_t id, NetMsg::ChatInfo& info);

	/*
	* 保存世界聊天记录(switch) / 保存军团聊天记录(world)
	* param
	* uid：source+server_id(switch) / 军团ID(world)
	* info：聊天记录
	*/
	void addWorldChatRecord(uint64_t uid, NetMsg::ChatInfo& info);

	/*
	* 获取玩家聊天记录
	* param
	* id：玩家ID
	* offLineMsg：聊天记录
	*/
	void getUserOfflineMsg(uint32_t id, google::protobuf::RepeatedPtrField<NetMsg::ChatInfo>* offLineMsg);

	/*
	* 获取世界聊天记录(switch) / 获取军团聊天记录(world)
	* param
	* uid：source+server_id(switch) / 军团ID(world)
	* recode：聊天记录
	*/
	void getWorldChatRecord(uint64_t uid, google::protobuf::RepeatedPtrField<NetMsg::ChatInfo>* record);

	/*
	* 删除玩家聊天记录
	* param
	* id：玩家ID
	*/
	void removeOfflineMsg(uint32_t id);
public:
	typedef std::deque<NetMsg::ChatInfo> ChatInfoDeque;
	typedef std::map<uint64_t, ChatInfoDeque> ChatRecordMap;
private:
	// 世界聊天记录（或者军团聊天记录）缓存 
	ChatRecordMap m_worldChatRecord;

	// 玩家聊天信息缓存
	std::map<uint32_t, google::protobuf::RepeatedPtrField<NetMsg::ChatInfo> > m_userOfflineMsgMap;
};
