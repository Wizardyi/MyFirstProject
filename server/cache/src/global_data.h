#pragma once

class server_config_t;
class Service;
class CRedisClient;

extern server_config_t *g_server_config;

extern Service* g_dbproxy;

extern CRedisClient* redis_client;
