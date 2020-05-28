#include "gen_msg_processor.h"
#include <stdlib.h>                      
#include <string.h>                      
#include <string>                        
#include <time.h>                        
                                         
extern "C" {                             
#include <libtaomee/crypt/qdes.h>        
}                                        
                                         
#include <libtaomee++/utils/strings.hpp> 
#include <libtaomee++/utils/strings.hpp> 
#include <libtaomee++/random/random.hpp> 
#include "cmd_procs.h"                   
#include "share/err.h"                   
#include "share/size_df.h"               
#include "server.h"                      
#include "utils.h"                       


#include <table/t_isg_account_info_table.h>


int CSAccountInfoInsertProcessor::process(userid_t userid, const char* body, int bodylen, std::string& ack_body)
{
        dbproto::CSAccountInfoData msg;                              
        msg.Clear();
		if (!msg.ParseFromArray(body, bodylen))
        {
                return db_err_proto_format_err;                        
        }

        dbproto::CSAccountInfoData ack;
        auto table = *(msg.mutable_table()->Mutable(0));

		g_accountInfoTable->insertTable(table.userid(), msg.mask(), table, userid);

        ack.SerializeToString(&ack_body);
	return 0;
}

int CSAccountInfoDeleteProcessor::process(userid_t userid, const char* body, int bodylen, std::string& ack_body);
{
		dbproto::CSAccountInfoData msg;
        msg.Clear();
        if (!msg.ParseFromArray(body, bodylen))
		{
                return db_err_proto_format_err;                        
        }
        auto table = *(msg.mutable_table()->Mutable(0));
		g_accountInfoTable->deleteTable(table.userid(),userid);
	return 0;
}

int CSAccountInfoUpdateProcessor::process(userid_t userid, const char* body, int bodylen, std::string& ack_body)
{
	dbproto::CSAccountInfoData msg;
	msg.Clear();

	if (!msg.ParseFromArray(body, bodylen)) 
		return db_err_proto_format_err;                        
	
	auto table = *(msg.mutable_table()->Mutable(0));
	g_accountInfoTable->updateTable(table.userid(), msg.mask(), table, userid);

	return 0;
}

int CSAccountInfoSelectProcessor::process(userid_t userid, const char* body, int bodylen, std::string& ack_body)
{
	dbproto::CSAccountInfoData msg;
	msg.Clear();
	if (!msg.ParseFromArray(body, bodylen))
		return db_err_proto_format_err;                        
	
	auto table = *(msg.mutable_table()->Mutable(0));
	dbproto::CSAccountInfoData ack;

	g_accountInfoTable->readTable(table.userid(), *(ack.mutable_table()), userid);
	ack.SerializeToString(&ack_body);

	return 0;
}

int CSAccountInfoUpdateAddProcessor::process(userid_t userid, const char* body, int bodylen, std::string& ack_body)
{
	dbproto::CSAccountInfoData msg;
	msg.Clear();

	if (!msg.ParseFromArray(body, bodylen))
		return db_err_proto_format_err;                        
	
	auto table = *(msg.mutable_table()->Mutable(0));
	g_accountInfoTable->updateAdd(table.userid(), msg.mask(), table, userid);

	return 0;
}

