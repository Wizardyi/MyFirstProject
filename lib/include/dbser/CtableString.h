/*
 * =====================================================================================
 * 
 *       Filename:  CtableString.h
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

#ifndef  CTABLESTRING_INCL
#define  CTABLESTRING_INCL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ctable.h"


class CtableString : public Ctable {
	protected:
		char table_name_pre[25];
		char db_name_pre[25];
		//ͨ�� id �õ�����(��ʽ�� dbname.table, ��: USER_00.t_user_pet_00 )
		// �õ��ı��������� this->tmp_table_name
		// ���� ����
		virtual char *get_table_name(const char *  str  );
	public:
		// table_name_pre : ������ǰ�沿�֣��磺 t_user_pet_00 --  t_user_pet_99, д�����t_user_pet 
		// id_name : ����id_is_existed������
		CtableString(mysql_interface * db, const char * db_name_pre,  
		 const char * table_name_pre) ;

		virtual ~CtableString(void){} 
};

#endif   /* ----- #ifndef CTABLESTRING_INCL  ----- */

