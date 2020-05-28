#pragma once

#include "cmd_processor_interface.h" 
#include "proto/db/dbproto.db.pb.h"  
#include "proto/db/dbproto.data.pb.h"
#include "proto/share/share.pb.h"    


class CSAccountInfoInsertProcessor: public CmdProcessorInterface
{
	public:
		int process(userid_t userid, const char* body, int bodylen, std::string& ack_body);
};

class CSAccountInfoDeleteProcessor: public CmdProcessorInterface
{
	public:
		int process(userid_t userid, const char* body, int bodylen, std::string& ack_body);
};

class CSAccountInfoUpdateProcessor: public CmdProcessorInterface
{
	public:
		int process(userid_t userid, const char* body, int bodylen, std::string& ack_body);
};

class CSAccountInfoSelectProcessor: public CmdProcessorInterface
{
	public:
		int process(userid_t userid, const char* body, int bodylen, std::string& ack_body);
};

class CSAccountInfoUpdateAddProcessor: public CmdProcessorInterface
{
	public:
		int process(userid_t userid, const char* body, int bodylen, std::string& ack_body);
};

