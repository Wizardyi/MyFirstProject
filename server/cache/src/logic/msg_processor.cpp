#include "msg_processor.h"
#include "proto/cache/cache.pb.h"
#include "global_data.h"
#include "utils.h"
#include "key_define.h"
#include "share/config/err.h"
#include "conn_manager.h"
#include "RedisClient.hpp"
#include "service.h"

/*
int LCCreateRoleProcessor::proc_pkg_from_client(db_proto_header_t* header, fdsession_t* fdsess, const char* body, int bodylen)
{
	cacheproto::CreateRole req;
	if(parse_message(body,bodylen,&req)){
		return -1;
	}


	cacheproto::CreateRole ack;
	utils::CheckSetAndGet(req,ack);


	TRACE_LOG("YZX test online to cache message,ackid:%d,sourcenumber:%s,serverid:%d:",ack.id(),ack.sourcenumber().c_str(),ack.serverid());
	return 0;

}

int WCGetOpenNewActivityProcessor::proc_pkg_from_client(db_proto_header_t* header, fdsession_t* fdsess, const char* body, int bodylen)
{
	cacheproto::GetOpenNewActivityReq req;
	if (parse_message(body, bodylen, &req)) 
		return send_err_to_conn(header,fdsess, cache_err_msg_format_err);
	
	std::stringstream key;
	key << req.source_id() << ":"
		<< req.server_id() << ":"
		<< KEY_NEWACTIVITY_IDS;

	std::string ids;
	int err = redis_client->Get(key.str(), &ids);
	if (err != RC_SUCCESS) 
	{
		ERROR_LOG("[zyw_activity] CSgetOpenNewActivityProcessor %s, error code: %d",key.str().c_str(),err);
		return -1;
	}
	
	cacheproto::GetOpenNewActivityAck ack;
	ack.set_source_id(req.source_id());
	ack.set_server_id(req.server_id());
	google::protobuf::util::JsonStringToMessage(ids,ack.mutable_ids());
	return send_msg_to_conn(header,fdsess,ack);
}

int WCSetOpenNewActivityProcessor::proc_pkg_from_client(db_proto_header_t* header, fdsession_t* fdsess, const char* body, int bodylen)
{
	cacheproto::SetOpenNewActivityReq req;
	if (parse_message(body, bodylen, &req)) 
		return send_err_to_conn(header,fdsess,cache_err_msg_format_err);

	std::stringstream key;
	key << req.source_id() << ":"
		<< req.server_id() << ":"
		<< KEY_NEWACTIVITY_IDS;

	std::string ids;
	google::protobuf::util::MessageToJsonString(req.ids(), &ids);
	int err = redis_client->Set(key.str(), ids);
	if (err != RC_SUCCESS) 
	{
		ERROR_LOG("[zyw_activity] CSsetOpenNewActivityProcessor %s error code: %d", key.str().c_str(),err);
		return -1;
	}
	return 0;
}
*/
