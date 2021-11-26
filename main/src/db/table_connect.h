#pragma once
#include"mysql.h"
#include<string.h>

#define  GEN_SQLSTR(sqlstr,...)  snprintf(sqlstr, sizeof(sqlstr),__VA_ARGS__ )
typedef unsigned uint32_t;

class CTableConnect
{
	public:
		CTableConnect(char *h_host,char *h_user,char *h_passwd,uint32_t h_port = 3306,char *h_db = nullptr);
		~CTableConnect(){

		}
		
	
		//查询语句
		int execute_query_sql(const char* sql,MYSQL_RES **result);

		//更新语句
		int execute_update_sql(const char *sql);
			
	public:
		MYSQL *conn;//数据库连接

	private:
		char host[16]; //ip
		char user[16]; //用户名
		char passwd[32]; //密码
		char db[32];	 //数据库
		uint32_t port; //端口
};

