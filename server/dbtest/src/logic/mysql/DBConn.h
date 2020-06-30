#ifndef	_CDBCONN_H_
#define _CDBCONN_H_

extern "C" {
	                         
#include <libtaomee/project/types.h> 
}

#include"mysql.h"
#include<string.h>

class CDBConn{
	private:
		char    host[16];
		char    user[16];
		char    pass[16];
		unsigned int m_port;

	public:
		MYSQL * conn;
		CDBConn(const char *h, const char *u, const char *p, unsigned int port=3306);
		~CDBConn();

		int exec_query_sql (const char *cmd, MYSQL_RES **result);
		int exec_update_sql(const char *cmd, int* affected_rows );
};


#endif
