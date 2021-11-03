#include "CTableRoute100x10.h"
#include<sstream>

CTableRoute100x10::CTableRoute100x10(std::shared_ptr<CTableConnect> conn_,const char* dbname,const char* tablename)
{
	conn = conn_;
	strcpy(db_name,dbname);
	strcpy(table_name,tablename);
}




int CTableRoute100x10::execute_query_sql(const char* sql,MYSQL_RES **result)
{
	if(conn == NULL){
		return 1;
	}

	int ret = conn->execute_query_sql(sql,result);
	return ret;
}


int CTableRoute100x10::execute_update_sql(const char *sql)
{
	if(conn == NULL){
		return 1;
	}

	int ret = conn->execute_update_sql(sql);
	return ret;
}


const char* CTableRoute100x10::get_table_name(uint32_t id)
{
	if(id == 0){
		return db_table_name;
	}

	uint32_t db_index = id % 100;
	uint32_t table_index = (id / 1000) % 10;
	std::stringstream oss;
	oss << db_name << "_"
		<< db_index << "."
		<< table_name  << "_"
		<< table_index;

	return oss.str().c_str();
}


