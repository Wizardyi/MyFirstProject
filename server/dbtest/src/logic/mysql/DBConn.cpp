#include"DBConn.h"
#include<stdio.h>
#include <stdlib.h>
#include <libtaomee/log.h>

CDBConn::CDBConn(const char *h, const char *u, const char *p, unsigned int port)
{
	strcpy(host, h);
	strcpy(user, u);
	strcpy(pass, p);
	m_port  = port;
	conn = mysql_init(NULL);
	conn = mysql_real_connect(conn, h, u, p, "test", 0, NULL, 0);
}

CDBConn::~CDBConn()
{
	 mysql_close(conn);
}

int CDBConn::exec_query_sql (const char *cmd, MYSQL_RES **result)
{
	DEBUG_LOG("exec sql:%s", cmd);
	int res = mysql_query(conn, cmd);
	if(res)
    	return res;
    *result = mysql_store_result(conn);
	return res;
}

int CDBConn::exec_update_sql(const char *cmd, int* affected_rows )
{
	DEBUG_LOG("exec sql:%s", cmd);
	int res = mysql_query(conn, cmd);	
	return res;
}





