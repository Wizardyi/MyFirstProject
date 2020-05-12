/*
 * =====================================================================================
 * 
 *       Filename:  Ctable.h
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  2007年11月06日 19时52分58秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  xcwen (xcwen), xcwenn@gmail.com
 *        Company:  TAOMEE
 * 
 * =====================================================================================
 */

#ifndef  CTABLE_INCL
#define  CTABLE_INCL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql_iface.h"
#include "benchapi.h"

#include <db_macro.h>
#include <proto_header.h>
#include <libtaomee++/proto/proto_base.h>
#ifdef USE_PROTOBUF
#	include <google/protobuf/descriptor.h>
#	include <google/protobuf/stubs/common.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>

	using google::protobuf::Message;
#endif

#define  GEN_SQLSTR(sqlstr,...)  snprintf( sqlstr, sizeof(sqlstr),__VA_ARGS__ )
class Ctable {
	protected:
		char sqlstr[1024*100]; 
		mysql_interface * db;
		char db_name[50];
		char table_name[50];
		//: db.table 
		char db_table_name[100];
		char dbser_return_buf[PROTO_MAX_SIZE];
		//用于保存主键值，缓存中使用,一般在get_table_name 中同步设置
		uint32_t id;
		bool 	use_cache;
	public:
		virtual char*  get_table_name();
		virtual char*  get_table_name(uint32_t id);

		//将 string 转成mysql str
		std::string get_mysql_str( const std::string &src );
		inline std::string get_mysql_str( const char * str, int str_len ){
			std::string s(str,str_len);
			return this->get_mysql_str(s);
		}
#ifdef USE_PROTOBUF
		inline std::string get_mysql_str_from_pb_obj( Message & msg ){
			std::string  ret;
			msg.AppendToString(&ret);
			return this->get_mysql_str( ret);
		}
#endif

		std::string get_mysql_str_from_cmessage( Cmessage & msg ){
			std::string  ret=msg.write_to_buf_ex();
			return this->get_mysql_str(ret);
		}

		 int select_data( char *&_p_result,	uint32_t &_pkg_len, MYSQL_RES* &res , uint32_t * p_count);

		int record_is_existed(char * sql_str,  bool * p_existed);
		int record_is_existed(char * sql_str,   int nofind_err);
		//影响行数为1行的 接口
		int exec_update_sql(char * sql_str, int nofind_err );
		int exec_insert_sql(char * sql_str, int existed_err );
		int exec_delete_sql(char * sql_str, int nofind_err );
		int exec_insert_sql_get_auto_increment_id(char * sql_str, int existed_err,
				uint32_t *p_increment_id );

		int exec_insert_sql_get_auto_increment_id(char * sql_str, int existed_err,
				uint64_t *p_increment_id );


		//影响行数为多行的接口( insert ,update ,delete,都可以使用)
		int exec_update_list_sql(char * sql_str, int nofind_err );

		Ctable(mysql_interface * db,const char * dbname,const char * tablename  ); 
		Ctable(mysql_interface * db); 

		virtual ~Ctable(void){} 
};

#endif   /* ----- #ifndef CTABLE_INCL  ----- */

