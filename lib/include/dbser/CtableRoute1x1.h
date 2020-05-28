/*
 * =====================================================================================
 * 
 *       Filename:  CtableRoute1x1.h
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

#ifndef  CTABLEROUTE1x1_INCL
#define  CTABLEROUTE1x1_INCL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CtableRoute.h"


class CtableRoute1x1 : public CtableRoute {
	protected:
		virtual char*  get_table_name(uint32_t id);
	public:
		virtual ~CtableRoute1x1(void){} 
		CtableRoute1x1(mysql_interface * db, const char * db_name_pre,  
		 const char * table_name_pre,const char* id_name ,const char* key2_name="" );


};

#endif   /* ----- #ifndef CTABLEROUTE_INCL  ----- */
