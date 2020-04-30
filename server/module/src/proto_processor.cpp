#include "proto_processor.h"
#include "share/module/proto.h"
#include "conn_manager.h"
#include "share/config/size_df.h"
#include "share/module/common.h"
#include "share/config/err.h"

ProtoProcessor* g_proto_processor;

ProtoProcessor::ProtoProcessor()
{
}

ProtoProcessor::~ProtoProcessor()
{
}

int ProtoProcessor::register_command(
        uint32_t cmd,
        CmdProcessorInterface* processor)
{
    cmd_processors_[cmd] = processor; 

    return 0;
}

int ProtoProcessor::get_pkg_len(int fd, const void* avail_data, 
       int avail_len, int from)
{
    if (from == PROTO_FROM_CLIENT) {
#ifdef CLIENT
        if (avail_len < (int)sizeof(cli_proto_header_t)) {
            return 0; // continue to recv        
        }
        cli_proto_header_t* header = (cli_proto_header_t *)avail_data;
        if (header->len < (int)sizeof(cli_proto_header_t)) {
            ERROR_LOG("too small pkg %u from client", header->len); 
            return -1;
        }
        if (header->len > (uint32_t)CLI_PROTO_MAX_LEN) {
            ERROR_LOG("too large pkg %u from client", header->len); 
            return -1;
        }
        return header->len;

#else
        if (avail_len < (int)sizeof(db_proto_header_t)) {
            return 0; // continue to recv        
        }
        db_proto_header_t* header = (db_proto_header_t *)avail_data;
        if (header->len < (int)sizeof(db_proto_header_t)) {
            ERROR_LOG("too small pkg %u from other svr", header->len); 
            return -1;
        }
        if (header->len > (uint32_t)OL_TO_SVR_LEN) {
            ERROR_LOG("too large pkg %u from other svr", header->len); 
            return -1;
        }
        return header->len;
#endif
    } else if (from == PROTO_FROM_SERV) {
        if (avail_len < (int)sizeof(db_proto_header_t)) {
            return 0; // continue to recv 
        } else {
            db_proto_header_t* header = (db_proto_header_t *)avail_data;
            if (header->len < (int)sizeof(db_proto_header_t)) {
                ERROR_LOG("too small pkg %u from server", header->len); 
                return -1;
            }
            if (header->len > (uint32_t)OL_TO_SVR_LEN) {
                ERROR_LOG("too large pkg %u from server", header->len); 
                return -1;
            }
            return header->len;
        }
    } else {
        ERROR_LOG("get pkg len invalid from %d", from); 
        return -1;
    }
}

int ProtoProcessor::proc_pkg_from_client(void* data, int len,
        fdsession_t* fdsess)
{
#ifdef CLIENT
    cli_proto_header_t* header = static_cast<cli_proto_header_t *>(data);
    const char* body = static_cast<char *>(data) + sizeof(cli_proto_header_t);
    int bodylen = header->len - sizeof(cli_proto_header_t);
	DEBUG_LOG("GET PKG FROM CLIENT [cmd:%u hex_cmd:0x%04X len:%u, seq(wait_u):%u fd:%d]",
            header->cmd, header->cmd, header->len, header->seq, fdsess->fd);
#else
    db_proto_header_t* header = static_cast<db_proto_header_t *>(data);
    const char* body = static_cast<char *>(data) + sizeof(db_proto_header_t);
    int bodylen = header->len - sizeof(db_proto_header_t);
	DEBUG_LOG("GET PKG FROM CLIENT [op_u:%u cmd:%u hex_cmd:0x%04X len:%u, seq(wait_u):%u fd:%d]",
            header->uid, header->cmd, header->cmd, header->len, header->seq, fdsess->fd);
#endif

	std::map<uint32_t, CmdProcessorInterface *>::iterator it;
    it = cmd_processors_.find(header->cmd);
    if (it == cmd_processors_.end()) {
		KERROR_LOG(0, "switch cmd is not transfer [cmd:%u]", header->cmd);
        // return send_err_to_conn(header, fdsess, switch_cmd_is_not_find_err);
		return 0;
    }
    CmdProcessorInterface *processor = it->second;		
	
	int ret = processor->proc_pkg_from_client(header, fdsess, body, bodylen);
	if (ret)
	{
		ERROR_LOG("proc pkg err [cmd:%u]", header->cmd);
		return send_err_to_conn(header, fdsess, ret);
	}

	return 0;
}

void ProtoProcessor::proc_pkg_from_serv(int fd, void* data, int len)
{
	db_proto_header_t* header = static_cast<db_proto_header_t *>(data);
	const char* body = (char *)data + sizeof(*header);
	int bodylen = len - sizeof(*header);

	DEBUG_LOG("GET PKG FROM SERVER [u:%u cmd:%u hex_cmd:0x%04X seq:%u ret:%d fd:%d]",
		header->uid, header->cmd, header->cmd, header->seq, header->ret, fd);

	std::map<uint32_t, CmdProcessorInterface *>::iterator it = cmd_processors_.find(header->cmd);
	if (it == cmd_processors_.end()) {
		// 过滤部分协议错误输出
		ERROR_LOG("Proc Svr Ret Pkg: cmd not find[op_u:%u cmd:%u hex_cmd:0x%04X seq:%u ret:%d]", 
				header->uid, header->cmd, header->cmd, header->seq, header->ret);  
		return;
	}

	CmdProcessorInterface* processor = it->second;
	int ret = header->ret;
	//包头有错误码
	if (ret) {

	}

	//返回错误码 照样处理
	ret = processor->proc_pkg_from_serv(header, NULL, body, bodylen);
	if (ret) {

	}
	return;
}
