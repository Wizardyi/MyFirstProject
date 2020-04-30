/*
* =====================================================================================
*
*  @file  dll_interface.cpp 
*
*  @brief  AsynServ的接口函数,AsynServ通过加载SO,处理具体的逻辑。
*
*  compiler  gcc4.3.2 
*	
*  platform  Linux
*
* copyright:  Inc. ShangHai CN. All rights reserved
*
* =====================================================================================
*/
#include "share/module/common.h"
#include "share/module/xmlutils.h"
#include "proto_processor.h"
#include "timer_procs.h"
#include "service.h"
#include "global_data.h"

static int init_cli_handle_funs();
static int init_connections();
static int load_uid_config(xmlNodePtr root);

#define CONFIG_READ_INTVAL(data, name) \
	do { \
		int ret = -1; \
		ret = config_get_intval(#name, ret); \
		if (ret == -1) { \
			ERROR_LOG("not find config '%s'", #name); \
			return -1; \
		} \
		data.name = ret; \
		INFO_LOG("set config '%s' = %d", \
#name, data.name); \
	} while (0);

#define CONFIG_READ_STRVAL(data, name) \
	do { \
		const char *conf_str = NULL; \
		conf_str = config_get_strval(#name); \
		if (conf_str == NULL) { \
			ERROR_LOG("not find config '%s'", #name); \
			return -1; \
		} \
		strncpy(data.name, conf_str, sizeof(data.name) - 1); \
		INFO_LOG("set config '%s' = '%s'",  \
#name, data.name); \
	} while (0);

/**
  * @brief AsyncServer框架要求实现的接口之一。 
  *
  */
extern "C" int  init_service(int isparent)
{
	if (!isparent) 
	{
#ifdef CLIENT
		INFO_LOG("SERVER FOR CLIENT");
		DEBUG_LOG("SERVER FOR CLIENT");
#else
		INFO_LOG("SERVER FOR SVR");
		DEBUG_LOG("SERVER FOR SVR");
#endif

		setup_timer();
		srand(time(NULL));
        srandom(time(NULL));

		g_proto_processor = new ProtoProcessor();

		INIT_LIST_HEAD(&g_reconnect_timer.timer_list);

		init_cli_handle_funs();
		register_timers();

		memset(&g_server_config, 0, sizeof(g_server_config));
		CONFIG_READ_STRVAL(g_server_config, conf_path);
		init_connections();

		// logic
		std::string uid_path = std::string(g_server_config.conf_path) + "/uid.xml";
		if (load_xmlconf(uid_path.c_str(), load_uid_config)) {
			KERROR_LOG(0, "load uid config failed.");
			return -1;
		}
	}

	return 0;
}

/**
  * @brief AsyncServer框架要求实现的接口之一。 
  *
  */
extern "C" int  fini_service(int isparent)
{
	if (!isparent) 
	{
		delete g_proto_processor;
		destroy_timer();
	}

	return 0;
}

/**
  * @brief AsyncServer框架要求实现的接口之一。 
  *
  */
extern "C" void proc_events()
{
	handle_timer();
}

/**
  * @brief AsyncServer框架要求实现的接口之一。 
  *
  */
extern "C" int  get_pkg_len(int fd, const void* avail_data, int avail_len, int isparent)
{
	if (isparent) {
        return g_proto_processor->get_pkg_len(fd, avail_data, avail_len, PROTO_FROM_CLIENT);
    } else {
        return g_proto_processor->get_pkg_len(fd, avail_data, avail_len, PROTO_FROM_SERV);
    }		
	return 0;	
}

/**
  * @brief AsyncServer框架要求实现的接口之一。 
  *
  */
extern "C" int  proc_pkg_from_client(void* data, int len, fdsession_t* fdsess)
{
	return g_proto_processor->proc_pkg_from_client(data, len, fdsess);
}

/**
  * @brief AsyncServer框架要求实现的接口之一。 
  *
  */
extern "C" void proc_pkg_from_serv(int fd, void* data, int len)
{
	return g_proto_processor->proc_pkg_from_serv(fd, data, len);
}

/**
  * @brief AsyncServer框架要求实现的接口之一。 
  *
  */
extern "C" void on_client_conn_closed(int fd)
{
}

/**
  * @brief AsyncServer框架要求实现的接口之一。 
  *
  */
extern "C" void on_fd_closed(int fd)
{
// 	if (fd == g_dbproxy->fd()) 
// 	{
// 		DEBUG_LOG("DB PROXY CONNECTION CLOSED\t[fd=%d]", g_dbproxy->fd());
// 		g_dbproxy->close();
//         if (g_dbproxy->connect() != 0) {
//             DEBUG_TLOG("add proxy conn timer");
//             ADD_TIMER_EVENT_EX(&g_reconnect_timer,
//                     kTimerTypeReconnectServiceTimely,
//                     g_dbproxy,
//                     get_now_tv()->tv_sec + kTimerIntervalReconnectServiceTimely);
//         }
// 	}
}

/**
  * @brief 处理广播包
  */
extern "C" void proc_mcast_pkg(const void* data, int len)
{
	/*const mcast_pkg_t* pkg = reinterpret_cast<const mcast_pkg_t*>(data);
	if (pkg->server_id != get_server_id()) {
		switch (pkg->main_cmd) {
		case mcast_reload_conf:
			reload_conf_op(pkg->minor_cmd, pkg->body, len - sizeof(mcast_pkg_t));
			break;
		default:
			ERROR_LOG("unsurported cmd %u", pkg->main_cmd);
			break;
		}
	}*/
	/*
	const db_proto_header_t* header = static_cast<const db_proto_header_t*>(data);
	const char* body = static_cast<const char*>(data) + sizeof(db_proto_header_t);
	int bodylen = header->len - sizeof(db_proto_header_t);

	KINFO_LOG(0, "proc mcast pkg cmd:%u", header->cmd);
	if (header->cmd == 0) {
		reloadproto::mcast_reload_conf reload_msg;
		if (parse_message(body, bodylen, &reload_msg)) {
			ERROR_LOG("decode mcast_proto  failed");
			return;
		}
		// ConfigData::ConfigDataManager::Instance()->load("../src/etc/config_data");
		// std::string conf_name = reload_msg.conf_name();
        // KINFO_LOG(0, "reload conf %s", conf_name.c_str());
		// if ((conf_name.compare("award_award_table.txt") == 0
		// 		|| conf_name.compare("pvp_rankaward_table.txt") == 0
		// 		|| conf_name.compare("award_group_table.txt") == 0)
		// 		&& CAwardMgr::get_mutable_instance().Reload()) {
		// 	INFO_LOG("reload %s success.", conf_name.c_str());
		// }
		// else {
		// 	ERROR_LOG("reload %s failed.", conf_name.c_str());
		// }
	}
	*/
}

/*
 * @brief 初始化客户端的处理函数
 * */
int init_cli_handle_funs()
{
//    // online->switch
//    g_proto_processor->register_command(switch_register_online_cmd, 
//			new RegisterOnlineCmdProc());
	return 0;
}

/*
 * @brief 初始化连接
 * */
int init_connections()
{
//    // 初始化dbproxy
//    char *dbproxy_name = config_get_strval("dbproxy_name");
//    if (!dbproxy_name) {
//        ERROR_TLOG("NO DBPROXY CONFIG FOUND IN BENCH.CONF");
//        return -1;
//    }
//    string tmp = string(dbproxy_name);
//    g_dbproxy = new Service(tmp);
//    ADD_TIMER_EVENT_EX(&g_reconnect_timer, 
//            kTimerTypeReconnectServiceTimely, 
//            g_dbproxy,
//            get_now_tv()->tv_sec + kTimerIntervalReconnectServiceTimely); 

    return 0;
}

int load_uid_config(xmlNodePtr root)
{
	std::set<std::string> set_uid;
	set_uid.clear();
	xmlNodePtr cur = root->xmlChildrenNode;
	while (cur) {
		if (!xmlStrcmp(cur->name, (const xmlChar *)"Ip")) {
			std::string str_userid;
			taomee::get_xml_prop(str_userid, cur, "ID");
			set_uid.insert(str_userid);
		}
		cur = cur->next;
	}

	std::set<std::string>::iterator it = set_uid.begin();
	for (; it != set_uid.end(); it++) {
		INFO_LOG("load uid config %s", (*it).c_str());
	}
	return 0;
}

