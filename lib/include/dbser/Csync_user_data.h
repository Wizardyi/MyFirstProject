/*
 * =====================================================================================
 * 
 *       Filename:  Csync_user_data.h
 * 
 *    Description:  
 * 
 *        Version:  1.0
 *        Created:  2007��11��06�� 19ʱ52��58�� CST
 *       Revision:  none
 *       Compiler:  gcc
 * 
 *         Author:  xcwen (xcwen), xcwenn@gmail.com
 *        Company:  TAOMEE
 * 
 * =====================================================================================
 */

#ifndef  Csync_user_data_INCL
#define  Csync_user_data_INCL
#include "libtaomee++/utils/tcpip.h" 
#include "Ctable.h" 
struct stru_str_with_len{
        uint32_t    len;
        char        str[];
}__attribute__((packed));

//�ֱ�ֿ�����Ͷ���
enum enum_db_table_type{
	type_100x10=1,
	type_100x100
};

class Csync_user_data {
	protected:
		char sql_str[8192];
		mysql_interface * db;
	public:
		Csync_user_data(mysql_interface * db, char * db_old_ip,short db_old_port ); 

		//���ܣ���� dbname_pre.tablename_pre  ��"useridname"=userid �ǲ��Ǵ��ڡ�
		//(��ֱ�ֿ��������:db_table_type)
		//
		//��������ڣ���ȥͬ��,(�������get_sql_date_cmdid), 
		//����Ѿ����ڣ�ֱ�ӷ���SUCC.
		int sync_data(const uint32_t userid,uint16_t get_sql_date_cmdid, 
				const char * dbname_pre,const char * tablename_pre ,
				enum_db_table_type db_table_type=type_100x10,
			   const char * useridname="userid"	);
		virtual ~Csync_user_data(void){} 
	private:
		Ctcp tcp;//���ڵõ��û���ԭ�������ϵ���������
		Ctable user_table; //���ڼ���û������Ƿ����
};

#endif   /* ----- #ifndef Csync_user_data_INCL  ----- */

