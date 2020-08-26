#ifndef __REDIS_SERVICE_H_
#define __REDIS_SERVICE_H_

#include "RedisClient.hpp"


class RedisClientManager {
public:

	//开始连接
	static bool conn_init(void);

	//释放链接
	static bool conn_fini(void);
};

#endif

