#include <sys/time.h>
#include <string>
#include <limits>
#include <libtaomee++/inet/pdumanip.hpp>
#include <libtaomee++/bitmanip/bitmanip.hpp>
#include <libtaomee++/utils/strings.hpp>

extern "C" {
#include <libtaomee/conf_parser/config.h>
#include <libtaomee/log.h>
}

#include "redis_service.h"

CRedisClient* redis_client = NULL;

/*
 * @brief 初始化连接
 * */
bool RedisClientManager::conn_init(void)
{
	const char *host_ip		= config_get_strval("redis_svr_ip");
	const char* instance_id = config_get_strval("redis_instance_id");
	const char* passwd		= config_get_strval("redis_passwd");

	string host = "localhost";
	int port = config_get_intval("redis_svr_port", 6379);

	std::string strInstanceID;
	std::string strPasswd;

	if (host_ip)
	{
		host = host_ip;
	}

	if (instance_id) {
		strInstanceID = instance_id;
	}

	if (passwd) {
		strPasswd = passwd;
	}

	redis_client = new CRedisClient();
	// 第3个参数为2，表示建立连接如果超过2秒，没建立成功，会超时返回，建立失败，会重试一次
	// 第4个参数为1，表示建立1条连接，因为本服务器是单进程，使用多条连接没有意义
	if (!redis_client->Initialize(host, port, 2, 1, strInstanceID, strPasswd))
	{
		KERROR_LOG(0, "Connection redis svr failed !");
		return false;
	}
	
	if (NULL == redis_client)
	{	
		KERROR_LOG(0, "Connection redis svr error !");
		return false;
	}	
	return true;
}

/*
 * @brief 释放链接
 * */
bool RedisClientManager::conn_fini(void)
{
	if (redis_client)
	{
		delete redis_client;

		redis_client = NULL;
	}

	return true;
}
