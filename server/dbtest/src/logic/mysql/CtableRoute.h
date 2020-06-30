#ifndef _CTABLE_ROUTE_H_
#define _CTABLE_ROUTE_H_

#include"DBConn.h"
#include"Ctable.h"


class CtableRoute : public Ctable{
	protected:
		char table_name_pre[40];  //表名的前面部分：如： t_user_pet_00 写入的是t_user_pet
		char db_name_pre[40];  //库名前面部分 如： user_attr_00 写入的是user_attr_
		char db_table_name[100];

		virtual char*  get_table_name(uint32_t id);

	public:
		CtableRoute(CDBConn* conn,const char* db_name,const char * table_name);
};



#endif


