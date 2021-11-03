#include "CTable.h"
#include<sstream>

Ctable::Ctable(std::shared_ptr<CTableConnect> conn_,const char* dbname,const char* tablename)
{
	conn = conn_;
	strcpy(db_name,dbname);
	strcpy(table_name,tablename);
}




int Ctable::execute_query_sql(const char* sql,MYSQL_RES **result)
{
	if(conn == NULL){
		return 1;
	}

	int ret = conn->execute_query_sql(sql,result);
	return ret;
}


int Ctable::execute_update_sql(const char *sql)
{
	if(conn == NULL){
		return 1;
	}

	int ret = conn->execute_update_sql(sql);
	return ret;
}


const char* Ctable::get_table_name()
{
	std::stringstream oss;
	oss << db_name << "."
		<< table_name;

	return oss.str().c_str();
}


