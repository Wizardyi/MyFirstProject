#include"user_info.h"
#include<iostream>

UserInfo::UserInfo(CDBConn* db)
	: CtableRoute100x10(db,"ISG","user_info")
{

}


int UserInfo::GetData(uint32_t userid)
{
	GEN_SQLSTR(this->sqlstr,
		    "SELECT UNIX_TIMESTAMP(last_login) FROM %s WHERE id = %u",
		    this->get_table_name(userid), userid);
	
	MYSQL_RES* res = NULL;                                
	MYSQL_ROW  row;                                       
	int ret = this->db->exec_query_sql(sqlstr, &res);     
	if (ret)                                              
	{                                                     
	    ERROR_LOG("exec sql failed: %s", this->sqlstr);   
	    return ret;                                       
	}                                                     
                                                      
	while ((row = mysql_fetch_row(res)) != NULL)          
	{                                                     
		std::cout << row[0] << std::endl;
	}
	return ret;
}



