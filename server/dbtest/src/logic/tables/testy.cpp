#include "testy.h"
#include "proto/share/share.pb.h"
#include<iostream>

TestTable::TestTable(CDBConn* db)
	: Ctable(db, "ISG_ACCOUNT", "yzx_test")
{

}

int TestTable::addData(uint32_t uid,const std::string& nick,uint32_t serverid,uint32_t &userid)
{
	GEN_SQLSTR(this->sqlstr,"INSERT INTO %s (uid,nick,server_id) VALUES (%u,'%s',%u)",
			this->get_db_table_name(),
			uid,
			nick.c_str(),
			serverid);

 	int ret = this->exec_insert_sql_get_auto_increment_id(this->sqlstr, 0, userid);
	if (ret != 0)
	{
		ERROR_LOG("exec sql failed: %s", this->sqlstr);
	}
	return ret;
}

int TestTable::getData()
{
	GEN_SQLSTR(this->sqlstr,
        "SELECT id FROM %s",
        this->get_db_table_name());

	 MYSQL_RES* res = NULL;
	 MYSQL_ROW row;
	 int ret = this->db->exec_query_sql(sqlstr, &res);
	 if (ret) {
		 ERROR_LOG("exec sql failed:%s", this->sqlstr);
	     return ret;
	 }
	 while((row = mysql_fetch_row(res)) != NULL) {
		uint32_t userid = atoi_safe(row[0]);	
		std::cout << userid << std::endl;
	 }
	mysql_free_result(res);
	return 0;

}

int TestTable:: updateData(uint32_t id,uint32_t server_id)
{
	GEN_SQLSTR(this->sqlstr,
			"UPDATE %s set server_id = %d where `id` = %d",
			this->get_db_table_name(),server_id,id);

	int affectedRows = 0;
	int ret = this->db->exec_update_sql(this->sqlstr,&affectedRows);
	if(ret != 0)
	{
		 ERROR_LOG("exec sql failed: %s", this->sqlstr);
	}
	return ret;

}

/*
int TestTable::getRoleInfos(uint32_t uid,dbproto::GetRoleInfoAck &ack)
{
	GEN_SQLSTR(this->sqlstr,
    	"SELECT id,nick,server_id FROM %s WHERE uid = %u",
   		this->get_table_name(), uid);
	
	 MYSQL_RES* res = NULL;
	 MYSQL_ROW row;
	 int ret = this->db->exec_query_sql(sqlstr, &res);
	 if (ret) {
	     return ret;
	 }

	 while ((row = mysql_fetch_row(res)) != NULL){
		shareproto::RoleInfo* info = 	ack.add_infos();
	    info->set_id(atoi_safe(row[0]));
		info->set_nick(row[1]);
	    info->set_server_id(atoi_safe(row[2]));
	 }

	mysql_free_result(res);
	return 0;
	

}
*/
