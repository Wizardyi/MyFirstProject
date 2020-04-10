#include <stdint.h>
#include "share/proto.h"
#include "server.h"
#include "proto_processor.h"
#include "global_data.h"
#include "utils.h"
#include "login_auth/http_client_thread.h"
#include "login_auth/login_auth_manager.h"
#include "login_auth/source_config.h"
#include "proto/share/share.pb.h"
#include <google/protobuf/util/json_util.h>




void login_auth_handle_func(authdata_t *authdata)
{
    if (authdata)
    {
		g_proto_processor->proc_pkg_from_http_serv(authdata);
    }
    else {
        KERROR_LOG(0, "http serv call back is NULL");
	}
}


int auth_session_to_httpserv(CUser* user,uint32_t cmd,const std::string& content,const std::string& extrastr)    
{                                                                                    
    clidata_t cli_data;
    login_auth_input_t login_auth_input;
    login_auth_input.server_id = g_server_config.service;
    login_auth_input.cli_cmd = cmd;
	login_auth_input.user_id = user->GetUserId();
    login_auth_input.platform_id = 9527;
    char  tokenId[32] = {0};
	snprintf(tokenId,32,"%d",user->GetUserId());
	shareproto::TextCheck Data;
    Data.set_text(content);
    Data.set_tokenid(tokenId);
    std::string pstr;
    google::protobuf::util::MessageToJsonString(Data, &pstr);
	snprintf(login_auth_input.sess_id, sizeof(login_auth_input.sess_id), "%s", pstr.c_str());
	snprintf(login_auth_input.extra_data, sizeof(login_auth_input.extra_data), "%s", extrastr.c_str());
    CSourceBaseAuto* poSourceBase = CSourceAutoManager::Instance().CreateSourceData(9527);
    if(poSourceBase == nullptr) {
        ERROR_LOG("Invalid Platform id:%d", login_auth_input.platform_id);
        return 0;
  	}
    login_auth_input.po_source_info = poSourceBase;
                                             
    int ret = sLoginAuthMgr.session_auth_req(&login_auth_input,
            user->fdsession);
	if (ret)
	{
		return user->send_err_to_player(cmd,ErrCode::DataError);
	}
    return 0;
}







