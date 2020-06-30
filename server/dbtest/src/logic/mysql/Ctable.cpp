#include "Ctable.h"
#include<iostream>

Ctable::Ctable(CDBConn* conn,const char* db_name,const char * table_name)
{
	db = conn;
	strcpy(m_db_name,db_name);
	strcpy(m_table_name,table_name);
	strcpy(m_db_table_name,db_name);
	strcat(m_db_table_name, ".");
	strcat(m_db_table_name, table_name);
}

char* Ctable::get_db_table_name()
{
	return m_db_table_name;
}

int Ctable::exec_insert_sql_get_auto_increment_id(char* cmd,int* affected_rows,uint32_t &id)
{
	int ret = db->exec_update_sql(cmd,affected_rows);
	char getsql[1024];
	GEN_SQLSTR(getsql,"SELECT LAST_INSERT_ID()");
	MYSQL_RES* res = NULL;
	MYSQL_ROW row;
	ret = db->exec_query_sql(getsql,&res);
	if(ret){
		return ret;
	}
	if ((row = mysql_fetch_row(res)) != NULL) {
		    id = atoi(row[0]);
	}
	mysql_free_result(res);
	return ret;
}
