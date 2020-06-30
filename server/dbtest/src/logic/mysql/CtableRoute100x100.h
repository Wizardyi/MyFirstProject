#ifndef CTABLEROUTE100x100_H
#define CTABLEROUTE100x100_H
#include "CtableRoute.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class CtableRoute100x100 : public CtableRoute{
	protected:
	     virtual char*  get_table_name(uint32_t id);
	public:
	     virtual ~CtableRoute100x100(void){} 
         CtableRoute100x100(CDBConn* conn,const char* db_name,const char * table_name);
};

#endif
