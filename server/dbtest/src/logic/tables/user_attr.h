#ifndef _USER_ATTR_H_
#define _USER_ATTR_H_

extern "C" {
#include <libtaomee/project/types.h> 
}
#include <libtaomee/log.h> 
#include "../mysql/CtableRoute100x100.h"
#include "../mysql/db_macro.h"

class UserAttr : public CtableRoute100x100
{
	public:
		UserAttr(CDBConn* db);

		int GetData(uint32_t userid,uint32_t key);
};



#endif
