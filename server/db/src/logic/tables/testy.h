#ifndef __TEST_H_
#define __TEST_H_

extern "C" {
#include <libtaomee/project/types.h>
}
#include<mysql.h>
#include <dbser/mysql_iface.h>
#include <Ctable.h> 
#include "proto/db/db.pb.h"

class TestTable : public Ctable
{
	public:
		TestTable(mysql_interface* db);

		int addData(uint32_t uid,const std::string& nick,uint32_t serverid,uint32_t &userid);

		int getData(uint32_t uid,uint32_t server_id,uint32_t &userid);
	
		int getRoleInfos(uint32_t uid,dbproto::GetRoleInfoAck &ack);
};


#endif
