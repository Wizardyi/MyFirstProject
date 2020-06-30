#pragma once
#include "../cmd_processor_interface.h"
#include "proto/db/db.pb.h"



class  CreateRoleProc : public CmdProcessorInterface
{
	public:
		int process(userid_t userid, const char* body, int bodylen, std::string& ack_body);
};

class LDGetRoleInfoProc : public CmdProcessorInterface
{
	public:
		int process(userid_t userid, const char* body, int bodylen, std::string& ack_body);
};

