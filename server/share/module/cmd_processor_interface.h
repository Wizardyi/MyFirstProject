#ifndef __CMD_PROCESSOR_INTERFACE_H__
#define __CMD_PROCESSOR_INTERFACE_H__

#include "proto.h"
#include "common.h"

#ifdef CLIENT
class CPlayer;
#endif

class CmdProcessorInterface
{
public:

    /**
     * @brief  proc_pkg_from_client 响应client请求包
     *
     * @param body 请求包体
     * @param bodylen 请求包体长度
     *
     * @return 0 处理成功 -1 处理失败
     */
#ifdef CLIENT
    virtual int proc_pkg_from_client(
            std::shared_ptr<CPlayer>,
			const char* body,
            int bodylen) = 0;

    virtual int proc_pkg_from_client(
            cli_proto_header_t* header,
            fdsession_t* fdsess,
			const char* body,
            int bodylen) = 0;
#else
    virtual int proc_pkg_from_client(
            db_proto_header_t* header,
            fdsession_t* fdsess,
			const char* body,
            int bodylen) = 0;
#endif

    /**
     * @brief  proc_pkg_from_serv 响应dbserver返回包
     *
     * @param body 返回包体
     * @param bodylen 返回包体长度
     *
     * @return 0 处理成功 -1 处理失败
     */
#ifdef CLIENT
    virtual int proc_pkg_from_serv(
            std::shared_ptr<CPlayer>,
            const char *body,
            int bodylen) = 0;
#endif
    virtual int proc_pkg_from_serv(
            db_proto_header_t* header,
            fdsession_t* fdsess,
            const char *body,
            int bodylen) = 0;

    /**
     * @brief  proc_errno_from_serv 处理dbserver返回的错误码
     *
     * @param client 客户端缓存
     * @param ret dbserver返回的错误码
     *
     * @return 返回online的错误码
     */
    virtual uint32_t proc_errno_from_serv(
            db_proto_header_t* header, fdsession_t* fdsess, uint32_t ret) 
    {
		return 0;
    }
};

inline int parse_message(
        const char* body, int bodylen, 
        google::protobuf::Message* message)
{
	message->Clear();

    if (!message->ParseFromArray(body, bodylen)) {
        std::string errstr = message->InitializationErrorString();
        ERROR_LOG("PARSE MSG failed, err = '%s'", errstr.c_str());
        return -1; 
    }

    std::string debug_str = message->Utf8DebugString();
    TRACE_LOG("PARSE MSG[%s] OK\nmsg:\n[%s]", 
            message->GetTypeName().c_str(), debug_str.c_str());
    
    return 0;
}

#endif
