#ifndef RELOAD_CONF_H
#define RELOAD_CONF_H

#define MAX_PKG_SIZE    (1024)

#include "commom.h"
#include "../../../proto/online/reload.pb.h"
#include <boost/lexical_cast.hpp>

struct db_proto_header_t
{
    uint32_t len;   
    uint32_t seq;
    uint16_t cmd;
    uint32_t ret;
    uint32_t uid;
} __attribute__((packed));

class reload_mgr_t
{
public:
	reload_mgr_t() : mcast_fd_(-1), mcast_port_(0) {
		memset(&mcast_addr_, 0, sizeof(mcast_addr_));
		memset(mcast_ip_, 0, sizeof(mcast_ip_));
		memset(out_ip_, 0, sizeof(out_ip_));
		memset(out_iface_, 0, sizeof(out_iface_));
	}
	bool init(char *mcast_ip, int16_t mcast_port, char* out_ip, char* out_iface); 
	bool connect();
	int32_t send(std::string &str);
	int32_t send(const google::protobuf::Message* message);

	bool is_connect() { return mcast_fd_ >= 0 ;}
private:
	int mcast_fd_;
	struct sockaddr_in mcast_addr_;
	char mcast_ip_[16];
	int16_t mcast_port_;
	
	char out_ip_[16];
	char out_iface_[16];

public:
	char sendbuff[MAX_PKG_SIZE];
	int32_t sendlen;
};

#endif
