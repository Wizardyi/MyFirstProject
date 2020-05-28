#include "testy.h"
#include "proto/share/share.pb.h"

TestTable::TestTable(mysql_interface* db)
	: Ctable(db, "ISG_ACCOUNT", "yzx_test")
{

}

int TestTable::addData(uint32_t uid,const std::string& nick,uint32_t serverid,uint32_t &userid)
{
	GEN_SQLSTR(this->sqlstr,"INSERT INTO %s (uid,nick,server_id) VALUES (%u,'%s',%u)",
			this->get_table_name(),
			uid,
			nick.c_str(),
			serverid);

	//int ret = this->exec_update_sql(this->sqlstr,USER_ID_NOFIND_ERR);
 	int ret = this->exec_insert_sql_get_auto_increment_id(this->sqlstr, KEY_EXISTED_ERR, &userid);
	if (ret != 0)
	{
		ERROR_LOG("exec sql failed: %s", this->sqlstr);
	}
	return ret;
}

int TestTable::getData(uint32_t uid,uint32_t server_id,uint32_t &userid)
{
	GEN_SQLSTR(this->sqlstr,
        "SELECT id FROM %s WHERE uid = %u  and server_id = %d limit 1",
        this->get_table_name(), uid, server_id);

	 MYSQL_RES* res = NULL;
	 MYSQL_ROW row;
	 int ret = this->db->exec_query_sql(sqlstr, &res);
	 if (ret) {
	     return ret;
	 }
	 if ((row = mysql_fetch_row(res)) != NULL) {
		userid = atoi_safe(row[0]);		
	 }
	
	mysql_free_result(res);
	return 0;

}


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

