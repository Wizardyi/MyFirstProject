#ifndef __SERVICE_H__
#define __SERVICE_H__

#include "share/module/common.h"
#include "share/config/size_df.h"

class Service
{
public:  
    Service(const std::string& service_name);
    ~Service();

    inline const std::string& service_name() const
    {
        return service_name_; 
    }

    inline int fd() const
    {
        return fd_;
    }

    int connect();

    int close();

    static void on_connect_callback(int fd, void* args);
    
    int send_buf(uint32_t userid, uint16_t cmd, uint32_t seq,
            const char* body, int bodylen);
    int send_msg(uint32_t userid, uint16_t cmd, uint32_t seq, 
            const google::protobuf::Message& message);
    int send_cmsg(uint32_t userid, uint16_t cmd, uint32_t seq,
            Cmessage *msg);
	int send_cmd(uint16_t cmd, uint32_t uid=0);
private:

    inline void set_fd(int fd) {
        fd_ = fd; 
    }

    int fd_;
    std::string service_name_;
    char send_buf_[OL_TO_SVR_LEN];
};

#endif
