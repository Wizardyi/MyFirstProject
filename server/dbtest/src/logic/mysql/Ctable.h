#ifndef _CTABLE_H_
#define _CTABLE_H_

#include"DBConn.h"

#define  GEN_SQLSTR(sqlstr,...)  snprintf( sqlstr, sizeof(sqlstr),__VA_ARGS__ )

class Ctable{
	protected:                                
   		char sqlstr[1024*100];                
    	char m_db_name[50];                     
    	char m_table_name[50];                  
    	//: db.table                          
    	char m_db_table_name[100];
		CDBConn* db; 
   public:
	Ctable(CDBConn* conn,const char* db_name,const char * table_name);
	
	virtual char*  get_db_table_name();
	virtual char*  get_table_name(uint32_t id);

	int exec_insert_sql_get_auto_increment_id(char* cmd,int* affected_rows,uint32_t &id);
};



#endif
