#ifndef __CMD_PROCESSOR_INTERFACE_H_
#define __CMD_PROCESSOR_INTERFACE_H_

#include <google/protobuf/message.h>
#include <libtaomee/project/types.h>
#include <libtaomee/log.h>

class CmdProcessorInterface
{
public:
    virtual ~CmdProcessorInterface() { }

    virtual int process(
            userid_t userid,
            const char* body, int bodylen,
            std::string& ack_body) = 0;
};

inline int parse_message(
        const char* body, int bodylen,
        google::protobuf::Message* message)
{
    message->Clear();

    std::string name = message->GetTypeName();
    if (!message->ParseFromArray(body, bodylen)) {
        std::string errstr = message->InitializationErrorString();
        ERROR_LOG("PARSE MSG '%s' failed, err = '%s'", 
                name.c_str(), errstr.c_str());
        return -1; 
    }

    std::string debug_str = message->Utf8DebugString();
    DEBUG_LOG("PARSE MSG:'%s' LEN:%u ok\nMSG:\n[%s]", 
            name.c_str(), (uint32_t)debug_str.size(), debug_str.c_str());

    return 0;
}

#endif
