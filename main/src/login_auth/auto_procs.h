#ifndef __AUTH_PROCS_H_
#define __AUTH_PROCS_H_

#include <map>
#include "login_auth/login_auth_manager.h"


void login_auth_handle_func(authdata_t *p_output);

//text校验
int auth_session_to_httpserv(CUser* user,uint32_t cmd,const std::string& content,const std::string& extrastr);

#endif
