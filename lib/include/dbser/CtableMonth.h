/*
 * =====================================================================================
 * 
 *       Filename:  CtableMonth.h
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

#ifndef  CTABLEMONTH_INCL
#define  CTABLEMONTH_INCL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CtableRoute.h"


class CtableMonth : public CtableRoute {
	protected:
	public:
		virtual char*  get_table_name();
		//֧��transid:3100000000 ,��ֱ��ָ���·�:200805
		virtual char*  get_table_name(uint32_t id);
		CtableMonth(mysql_interface * db,const char * db_name_pre,  
		const char * table_name_pre,const  char* id_name ) ;
		virtual ~CtableMonth(void){} 
};

#endif   /* ----- #ifndef CTABLEMONTH_INCL  ----- */

