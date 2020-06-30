#include"CtableRoute.h"


CtableRoute::CtableRoute(CDBConn* conn,const char* db_name,const char * table_name)
	: Ctable(conn,db_name,table_name)
{
	strcpy(db_name_pre,db_name);
	strcpy(table_name_pre,table_name);
}


