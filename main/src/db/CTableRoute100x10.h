#pragma once
#include "table_connect.h"
#include<string.h>
#include<memory>
#include<cstring>

class CTableRoute100x10
{
	public:
		CTableRoute100x10(std::shared_ptr<CTableConnect> conn_,const char* dbname,const char* tablename);
		~CTableRoute100x10(){

		}

		const char* get_table_name(uint32_t id = 0);
	
		int execute_query_sql(const char* sql,MYSQL_RES **result);
		int execute_update_sql(const char *sql);
	
	private:
		char sqlstr[100 * 1024];
		std::shared_ptr<CTableConnect> conn;
		char db_name[50];
		char table_name[50];
		char db_table_name[100];

};


