#ifndef _USER_INFO_H_
#define _USER_INFO_H_

extern "C" {
#include <libtaomee/project/types.h> 
}
#include <libtaomee/log.h> 
#include "../mysql/CtableRoute100x10.h"

class UserInfo : public CtableRoute100x10
{
	public:
		UserInfo(CDBConn* db);

		int GetData(uint32_t userid);
};



#endif
