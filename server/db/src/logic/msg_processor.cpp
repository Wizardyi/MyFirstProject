#include "msg_processor.h"
#include "../global_data.h"
#include "share/config/err.h"

int CreateRoleProc::process(userid_t userid, const char* body, int bodylen, std::string& ack_body)
{
	dbproto::LDCretaRole req;
	if(parse_message(body,bodylen,&req)){
		return -1;
	}

	dbproto::CreateRoleAck ack;
	uint32_t indexid  = 0;
	int ret = g_test_table->getData(req.uid(),req.server_id(),indexid);
	
	if(ret != 0)                   
	{	                              
		return db_err_operate_fail;
	}

	if(indexid != 0)
	{
		return db_err_role_already_exist;
	}

	ret = g_test_table->addData(req.uid(),req.nick(),req.server_id(),indexid);
	if(ret != 0)
	{
		return db_err_operate_fail;
	}

	ack.set_err(0);
	ack.set_id(indexid);

	ack.SerializeToString(&ack_body);
	return 0;
}

int LDGetRoleInfoProc::process(userid_t userid, const char* body, int bodylen, std::string& ack_body)
{
	dbproto::LDGetRoleInfo req;
	if(parse_message(body,bodylen,&req)){
		return -1;
	}

	dbproto::GetRoleInfoAck ack;
	int ret = 0;
	ret = g_test_table->getRoleInfos(req.uid(),ack);
	if(ret != 0)
	{
		return db_err_operate_fail;
	}

	ack.SerializeToString(&ack_body); 
	return 0;
}

