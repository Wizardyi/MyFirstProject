#ifndef __TEST_H_
#define __TEST_H_

extern "C" {
#include <libtaomee/project/types.h>
}
#include <libtaomee/log.h>
#include "../mysql/Ctable.h" 
#include "../mysql/db_macro.h" 

class TestTable : public Ctable
{
	public:
		TestTable(CDBConn* db);

		int addData(uint32_t uid,const std::string& nick,uint32_t serverid,uint32_t &userid);

		int getData();

		int updateData(uint32_t id,uint32_t server_id);

		//int getRoleInfos(uint32_t uid,dbproto::GetRoleInfoAck &ack);
};


#endif
