#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libtaomee++/utils/strings.hpp>
#include <dbser/benchapi.h>
#include "logic/mysql/Ctable.h" 

#include "share/module/proto.h"
#include "global_data.h"
#include "proto/db/db.pb.h"
#include "logic/msg_processor.h"

void pb_log_handler(google::protobuf::LogLevel level,
        const char *filename, int line, const std::string &message)
{
    static const char *level_names[] = {"INFO", "WARNING", "ERROR", "FATAL" };
    ERROR_LOG("[%s %s:%d] %s",
            level_names[level], filename, line, message.c_str());
    DEBUG_LOG("[%s %s:%d] %s",
            level_names[level], filename, line, message.c_str());
}

#define CONFIG_READ_INTVAL(data, name) \
    do { \
        int ret = -1; \
        ret = config_get_intval(#name, ret); \
        if (ret == -1) { \
            ERROR_LOG("not find config '%s'", #name); \
            return -1; \
        } \
        data.name = ret; \
        DEBUG_LOG("set config '%s' = %d", \
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
        DEBUG_LOG("set config '%s' = '%s'",  \
#name, data.name); \
    } while (0);

int init_tables(CDBConn* db)
{
    if (db == NULL) {
        return -1;    
    }

	g_test_table = new TestTable(db);
	g_user_info_table = new UserInfo(db);
	g_user_attr_table = new	UserAttr(db); 

	return 0;
}

int init_cmd_procs()
{
	return 0;
}

int handle_init(
        int argc, 
        char **argv, 
        int proc_type)
{
#ifdef ENABLE_TRACE_LOG
#ifdef USE_TLOG
    SET_LOG_LEVEL(tlog_lvl_trace);
    SET_TIME_SLICE_SECS(86400);
#endif
#endif

    if (proc_type == PROC_WORK) {

        SetLogHandler(pb_log_handler);

        processor = new ProtoProcessor();

        CONFIG_READ_STRVAL(g_config, mysql_host);
        CONFIG_READ_STRVAL(g_config, mysql_user);
        CONFIG_READ_STRVAL(g_config, mysql_passwd);
        CONFIG_READ_STRVAL(g_config, mysql_charset);
        CONFIG_READ_INTVAL(g_config, mysql_port);
        CONFIG_READ_STRVAL(g_config, log_db_name);
        CONFIG_READ_STRVAL(g_config, table_config_path);

		/*
		int ret = 0;

		g_db = new mysql_interface(                                            
      		g_config.mysql_host,                                               
      		g_config.mysql_user,                                               
      		g_config.mysql_passwd,                                             
      		g_config.mysql_port,                                               
      		NULL,                                                              
    		g_config.mysql_charset);                                           
                                                                         
                                                                         
		if (!g_db) {                                                            
			ERROR_LOG("init db failed");                                        
			return -1;                                                          
		}                                                                       
																			 
		 g_db->set_is_log_debug_sql(1);                                          
		 g_db->set_is_only_exec_select_sql(0);                                   
																				 
		 ret = 0;                                                            
		 ret = mysql_set_character_set(&g_db->handle, g_config.mysql_charset);   
		 if (ret != 0) {                                                         
			 ERROR_LOG("set charset '%s' failed", g_config.mysql_charset);       
			 return -1;                                                          
		 }                                                                      
			

		 */
		g_db = new CDBConn(g_config.mysql_host,  
				g_config.mysql_user,  
				g_config.mysql_passwd,
				g_config.mysql_port);

		if (!g_db) {                    
		    ERROR_LOG("init db failed");    
			return -1; 
		}

		int ret = 0;
		//关闭自动提交
		ret = mysql_autocommit(g_db->conn, 0);
		if(ret != 0)
		{
			ERROR_LOG("set autocommit false failed\n");
		}

		init_tables(g_db);

	
		uint32_t id = 0;
		g_test_table->addData(123,"saddas",21,id);
		std::cout << std::endl << id << std::endl;
		mysql_rollback(g_db->conn);
		//mysql_commit(g_db->conn);



        // 初始化协议函数
        ret = init_cmd_procs();
        if (ret != 0) {
            ERROR_LOG("init cmd procs failed");        
            return -1;
        }

        return 0;
    } else if (proc_type == PROC_CONN) {
        processor = new ProtoProcessor();
        return 0;
    }

    return 0;
}

int handle_input(
        const char* recv_buf, 
        int recv_len, 
        const skinfo_t* skinfo)
{
    return processor->get_pkg_len(recv_buf, recv_len);
}

int handle_process(
        char *recv, 
        int recv_len, 
        char** send_buf, 
        int* send_len, 
		const skinfo_t*)
{

	int ret = processor->process(recv, recv_len, send_buf, send_len);


	return ret;
}

void handle_fini(
        int proc_type)
{
    if (proc_type == PROC_WORK) {
        delete processor; 
    } else if (proc_type == PROC_CONN) {
        delete processor; 
    }
}

int handle_filter_key(const char *buf, int len, uint32_t *key)
{
    if (config_get_intval("dont_use_filter_key", 0) == 1) {
        return -1;
    }
    db_proto_header_t *header = (db_proto_header_t *)buf;
    *key = header->uid;
    return 0;
}
