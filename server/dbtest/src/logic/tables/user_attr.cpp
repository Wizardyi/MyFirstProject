#include"user_attr.h"
#include<iostream>

UserAttr::UserAttr(CDBConn* db)
	: CtableRoute100x100(db,"ISG","user_attr")
{

}


int UserAttr::GetData(uint32_t userid,uint32_t key)
{
	GEN_SQLSTR(this->sqlstr,
	        "SELECT `value`, `str_value` FROM %s WHERE `userid` = %u AND `key` = %u",
			this->get_table_name(userid), userid, key);
	
	uint32_t value = 0;
	std::string str_value;
	STD_QUERY_ONE_BEGIN(this->sqlstr, USER_ID_NOFIND_ERR);
		INT_CPY_NEXT_FIELD(value);
		str_value = NEXT_FIELD;
		std::cout << std::endl;
		std::cout << value << std::endl;
		std::cout << str_value << std::endl;
	STD_QUERY_ONE_END();
}



