#include "chat_record.h"

CChatRecordMgr::CChatRecordMgr()
{
}

CChatRecordMgr::~CChatRecordMgr()
{
}

void CChatRecordMgr::addUserOfflineMsg(uint32_t id, NetMsg::ChatInfo& info)
{
	NetMsg::ChatInfo* pMsg = m_userOfflineMsgMap[id].Add();
	pMsg->CopyFrom(info);
}

void CChatRecordMgr::addWorldChatRecord(uint64_t uid, NetMsg::ChatInfo& info)
{
	auto& chatRecordDeq = m_worldChatRecord[uid];
	if (chatRecordDeq.size() >= 100) {
		chatRecordDeq.pop_front();
	}
	chatRecordDeq.push_back(info);
}

void CChatRecordMgr::getUserOfflineMsg(uint32_t id, google::protobuf::RepeatedPtrField<NetMsg::ChatInfo>* offLineMsg)
{
	offLineMsg->CopyFrom(m_userOfflineMsgMap[id]);	
}

void CChatRecordMgr::getWorldChatRecord(uint64_t uid, google::protobuf::RepeatedPtrField<NetMsg::ChatInfo>* record)
{
	auto& chatRecordDeq = m_worldChatRecord[uid];
	for (auto& info : chatRecordDeq) {
		record->Add()->CopyFrom(info);
	}
}

void CChatRecordMgr::removeOfflineMsg(uint32_t id)
{
	m_userOfflineMsgMap.erase(id);
}
