#ifndef CTABLEROUTE100x10_H
#define CTABLEROUTE100x10_H
#include "CtableRoute.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class CtableRoute100x10 : public CtableRoute{
	protected:
	     virtual char*  get_table_name(uint32_t id);
	public:
	     virtual ~CtableRoute100x10(void){} 
         CtableRoute100x10(CDBConn* conn,const char* db_name,const char * table_name);
};

#endif
