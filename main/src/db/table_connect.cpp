#include"table_connect.h"


CTableConnect::CTableConnect(char *h_host,char *h_user,char *h_passwd,uint32_t h_port, char *h_db)
{
	strcpy(host,h_host);
	strcpy(user,h_user);
	strcpy(passwd,h_passwd);
	if(h_db != NULL)
		strcpy(db,h_db);
	port = h_port;

	conn = mysql_init(NULL);
	conn = mysql_real_connect(conn, host, user, passwd, db, port, NULL, 0);
}


int CTableConnect::execute_query_sql(const char* sql,MYSQL_RES **result)
{
	int res = mysql_query(conn, sql);
	if(res){
		return res;
	}else{
		*result = mysql_store_result(conn);
	}

	return 0;
}


int CTableConnect::execute_update_sql(const char *sql)
{
	int res = mysql_query(conn, sql);	
	if(res){
		return res;
	}

	return 0;
}




