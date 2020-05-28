#include "t_isg_account_info_table.h"
#include "share/err.h"
#include "utils.h"

CAccountInfoTable::CAccountInfoTable(mysql_interface* db)
      : Ctable(db, "ISG_ACCOUNT", "t_isg_account_info"){      
}

int CAccountInfoTable::readTable(int32_t userid, google::protobuf::RepeatedPtrField<dbproto::AccountInfo>& roInfo, userid_t userId){
    std::stringstream oss;
    oss << "SELECT `userid`,`source_number`,`source`,`server_id`,`sex`,`register_time`,`login_session`,`expire_time`,`device_id`,`platform`,`original_server_id`,`aaid`,`idfa`,`media_source`,`campaign` FROM " << this->get_table_name() ;

    GEN_SQLSTR(this->sqlstr, oss.str().c_str());
    MYSQL_RES* res = NULL;
    MYSQL_ROW  row;
    int ret = this->db->exec_query_sql(sqlstr, &res);
    if (ret) {
       ERROR_LOG("exec sql failed: %s", this->sqlstr);
       return ret; 
    }
    while ((row = mysql_fetch_row(res)) != NULL) {
        dbproto::AccountInfo* info = roInfo.Add();
	info->set_userid(atoi_safe(row[0]));
	info->set_source_number(row[1]);
	info->set_source(atoi_safe(row[2]));
	info->set_server_id(atoi_safe(row[3]));
	info->set_sex(atoi_safe(row[4]));
	info->set_register_time(atoi_safe(row[5]));
	info->set_login_session(row[6]);
	info->set_expire_time(atoi_safe(row[7]));
	info->set_device_id(row[8]);
	info->set_platform(atoi_safe(row[9]));
	info->set_original_server_id(atoi_safe(row[10]));
	info->set_aaid(row[11]);
	info->set_idfa(row[12]);
	info->set_media_source(row[13]);
	info->set_campaign(row[14]);
    }
    
    mysql_free_result(res);
    return 0;
}



int CAccountInfoTable::insertTable(int32_t userid, uint64_t bitSet, dbproto::AccountInfo& roInfo, userid_t userId){
    std::stringstream oss;
    oss << "INSERT INTO " << this->get_table_name();
    std::bitset<64> oBit(bitSet);
    std::stringstream ossName;
    std::stringstream ossVal;
    for(int32_t i = 0; i < dbproto::EnumAccountInfo::Enum_t_isg_account_info_Max; ++i) {
        if(oBit.test(i)) {
            switch(i)
            {
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_userid:
		{
		    if(!ossName.str().empty()){
		        ossName << ",";
		        ossVal << ",";
		    }
		    ossName << "`userid`";
		    ossVal << roInfo.userid();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_source_number:
		{
		    if(!ossName.str().empty()){
		        ossName << ",";
		        ossVal << ",";
		    }
		    ossName << "`source_number`";
		    ossVal << "'" << roInfo.source_number() << "'";
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_source:
		{
		    if(!ossName.str().empty()){
		        ossName << ",";
		        ossVal << ",";
		    }
		    ossName << "`source`";
		    ossVal << roInfo.source();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_server_id:
		{
		    if(!ossName.str().empty()){
		        ossName << ",";
		        ossVal << ",";
		    }
		    ossName << "`server_id`";
		    ossVal << roInfo.server_id();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_sex:
		{
		    if(!ossName.str().empty()){
		        ossName << ",";
		        ossVal << ",";
		    }
		    ossName << "`sex`";
		    ossVal << roInfo.sex();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_register_time:
		{
		    if(!ossName.str().empty()){
		        ossName << ",";
		        ossVal << ",";
		    }
		    ossName << "`register_time`";
		    ossVal << roInfo.register_time();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_login_session:
		{
		    if(!ossName.str().empty()){
		        ossName << ",";
		        ossVal << ",";
		    }
		    ossName << "`login_session`";
		    ossVal << "'" << roInfo.login_session() << "'";
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_expire_time:
		{
		    if(!ossName.str().empty()){
		        ossName << ",";
		        ossVal << ",";
		    }
		    ossName << "`expire_time`";
		    ossVal << roInfo.expire_time();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_device_id:
		{
		    if(!ossName.str().empty()){
		        ossName << ",";
		        ossVal << ",";
		    }
		    ossName << "`device_id`";
		    ossVal << "'" << roInfo.device_id() << "'";
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_platform:
		{
		    if(!ossName.str().empty()){
		        ossName << ",";
		        ossVal << ",";
		    }
		    ossName << "`platform`";
		    ossVal << roInfo.platform();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_original_server_id:
		{
		    if(!ossName.str().empty()){
		        ossName << ",";
		        ossVal << ",";
		    }
		    ossName << "`original_server_id`";
		    ossVal << roInfo.original_server_id();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_aaid:
		{
		    if(!ossName.str().empty()){
		        ossName << ",";
		        ossVal << ",";
		    }
		    ossName << "`aaid`";
		    ossVal << "'" << roInfo.aaid() << "'";
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_idfa:
		{
		    if(!ossName.str().empty()){
		        ossName << ",";
		        ossVal << ",";
		    }
		    ossName << "`idfa`";
		    ossVal << "'" << roInfo.idfa() << "'";
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_media_source:
		{
		    if(!ossName.str().empty()){
		        ossName << ",";
		        ossVal << ",";
		    }
		    ossName << "`media_source`";
		    ossVal << "'" << roInfo.media_source() << "'";
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_campaign:
		{
		    if(!ossName.str().empty()){
		        ossName << ",";
		        ossVal << ",";
		    }
		    ossName << "`campaign`";
		    ossVal << "'" << roInfo.campaign() << "'";
		}
		break;
            }
        }
    }
    oss << "(" << ossName.str() << ") values(" << ossVal.str() << ");";
    GEN_SQLSTR(this->sqlstr, oss.str().c_str());

    int ret = this->exec_insert_sql(this->sqlstr, KEY_EXISTED_ERR);;
    if (ret != DB_SUCC) 
    {
        ERROR_LOG("exec sql failed: %s", this->sqlstr);
    }
    return ret; 
}

int CAccountInfoTable::updateTable(int32_t userid, uint64_t bitSet, dbproto::AccountInfo& roInfo, userid_t userId){
  std::stringstream oss,ossVal;
  std::bitset<64> oBit(bitSet);
  for(int32_t i = 0; i < dbproto::EnumAccountInfo::Enum_t_isg_account_info_Max; ++i) {
        if(oBit.test(i)) {
            switch(i)
            {
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_userid:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`userid` = " << roInfo.userid();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_source_number:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`source_number` = " << "'" << roInfo.source_number() << "'";
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_source:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`source` = " << roInfo.source();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_server_id:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`server_id` = " << roInfo.server_id();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_sex:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`sex` = " << roInfo.sex();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_register_time:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`register_time` = " << roInfo.register_time();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_login_session:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`login_session` = " << "'" << roInfo.login_session() << "'";
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_expire_time:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`expire_time` = " << roInfo.expire_time();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_device_id:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`device_id` = " << "'" << roInfo.device_id() << "'";
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_platform:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`platform` = " << roInfo.platform();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_original_server_id:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`original_server_id` = " << roInfo.original_server_id();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_aaid:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`aaid` = " << "'" << roInfo.aaid() << "'";
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_idfa:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`idfa` = " << "'" << roInfo.idfa() << "'";
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_media_source:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`media_source` = " << "'" << roInfo.media_source() << "'";
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_campaign:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`campaign` = " << "'" << roInfo.campaign() << "'";
		}
		break;
            }
        }
    }
  oss << "UPDATE " << this->get_table_name() << " SET " << ossVal.str() << " WHERE `userid` = " << roInfo.userid();
  GEN_SQLSTR(this->sqlstr, oss.str().c_str());
  return this->exec_update_sql(this->sqlstr,USER_ID_NOFIND_ERR );
}

int CAccountInfoTable::updateAdd(int32_t userid, uint64_t bitSet, dbproto::AccountInfo& roInfo, userid_t userId){
  std::stringstream oss,ossVal;
  std::bitset<64> oBit(bitSet);
  for(int32_t i = 0; i < dbproto::EnumAccountInfo::Enum_t_isg_account_info_Max; ++i) {
        if(oBit.test(i)) {
            switch(i)
            {
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_userid:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`userid` = `userid` + " << roInfo.userid();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_source:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`source` = `source` + " << roInfo.source();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_server_id:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`server_id` = `server_id` + " << roInfo.server_id();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_sex:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`sex` = `sex` + " << roInfo.sex();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_register_time:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`register_time` = `register_time` + " << roInfo.register_time();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_expire_time:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`expire_time` = `expire_time` + " << roInfo.expire_time();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_platform:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`platform` = `platform` + " << roInfo.platform();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_original_server_id:
		{
		    if(!ossVal.str().empty()){
		        ossVal << ",";
		    }
		    ossVal << "`original_server_id` = `original_server_id` + " << roInfo.original_server_id();
		}
		break;
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_source_number:
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_login_session:
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_device_id:
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_aaid:
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_idfa:
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_media_source:
		case dbproto::EnumAccountInfo::Enum_t_isg_account_info_campaign:
			ERROR_LOG("can't add non numberic column campaign value in table t_isg_account_info");
			break;

            }
        }
    }
  oss << "UPDATE " << this->get_table_name() << " SET " << ossVal.str() << " WHERE `userid` = " << roInfo.userid();
  GEN_SQLSTR(this->sqlstr, oss.str().c_str());
  return this->exec_update_sql(this->sqlstr,USER_ID_NOFIND_ERR );
}

int CAccountInfoTable::deleteTable(int32_t userid,userid_t userId){
    std::stringstream oss;
    oss << "DELETE FROM " << this->get_table_name() << " WHERE `userid` = " << userid;
    GEN_SQLSTR(this->sqlstr, oss.str().c_str());
    int ret = this->exec_delete_sql(this->sqlstr, USER_ID_NOFIND_ERR);
    if (ret != DB_SUCC) 
    {
        ERROR_LOG("exec sql failed: %s", this->sqlstr);
    }
    return ret; 
}

