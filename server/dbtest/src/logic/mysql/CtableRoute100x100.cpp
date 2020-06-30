#include "CtableRoute100x100.h"


CtableRoute100x100::CtableRoute100x100(CDBConn* conn,const char* db_name,const char * table_name)
	: CtableRoute(conn,db_name,table_name)
{

}


char* CtableRoute100x100::get_table_name(uint32_t id)
{
	memset(this->db_table_name,0,sizeof(char)*100);
	strcpy(this->db_table_name,db_name_pre);
	strcat(this->db_table_name, "_");
	uint32_t dbindex = id % 100;
	char dst[100];
	snprintf(dst, sizeof(dst), "%d", dbindex);
	strcat(this->db_table_name,dst);
	strcat(this->db_table_name, ".");
	uint32_t tableindex = id / 100 % 100;
	char dst1[100];
	snprintf(dst1, sizeof(dst1), "%d", tableindex);
	strcat(this->db_table_name,table_name_pre);
	strcat(this->db_table_name, "_");
	strcat(this->db_table_name, dst1);
	return this->db_table_name;
}
