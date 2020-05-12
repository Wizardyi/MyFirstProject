/*
 * =====================================================================================
 * 
 *       Filename:  CtableWithKey.h
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

#ifndef  CTABLEWITHKEY_INCL
#define  CTABLEWITHKEY_INCL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ctable.h"


class CtableWithKey : public Ctable {
	protected:
		char id_name[25];
	public:
		// id_name : ����id_is_existed������
		virtual int id_is_existed(uint32_t id, bool * existed);
		CtableWithKey (mysql_interface * db,const  char * dbname, 
		const char * tablename,const char* id_name   ); 
		virtual ~CtableWithKey(void){} 
};

#endif   /* ----- #ifndef CTABLEWITHKEY_INCL  ----- */

