#include "reload_conf.h"

bool reload_mgr_t::init(char* mcast_ip, int16_t mcast_port,
		char* out_ip, char* out_iface)
{
	strcpy(mcast_ip_, mcast_ip);
	strcpy(out_ip_, out_ip);
	strcpy(out_iface_, out_iface);
	mcast_port_ = mcast_port;
	return connect();
}

bool reload_mgr_t::connect()
{
	mcast_fd_ = socket(AF_INET, SOCK_DGRAM, 0);
	if (mcast_fd_ == -1) {
		std::cout << "Failed Create Socket Err:" << errno 
			<< "strerrno: "<< strerror(errno) << std::endl;
		return false;
	}
	memset(&mcast_addr_, 0, sizeof(mcast_addr_));
	mcast_addr_.sin_family = AF_INET;
	inet_pton(AF_INET, mcast_ip_, &(mcast_addr_.sin_addr));
	mcast_addr_.sin_port = htons(mcast_port_);

	int on = 1;
	setsockopt(mcast_fd_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);
	in_addr_t ipaddr; 
	inet_pton(AF_INET, out_ip_, &ipaddr);
	if (setsockopt(mcast_fd_, IPPROTO_IP, IP_MULTICAST_IF, &ipaddr, sizeof ipaddr) == -1){
		std::cout << "Failed to Set Outgoing Interface:" << out_ip_ << "err:" <<
			errno << "stderrno:" << strerror(errno) << std::endl;
		return false;
	}
	struct group_req req;
	req.gr_interface = if_nametoindex(out_iface_);
	memcpy(&req.gr_group, &mcast_addr_, sizeof(mcast_addr_));
	if (setsockopt(mcast_fd_, IPPROTO_IP, MCAST_JOIN_GROUP, &req, sizeof(req)) == -1) {
		std::cout << "Failed to Join Mcast Grp:Err:" << errno <<
			"strerrno " << strerror(errno) << std::endl;
		return false;
	}
	return true;
}

int32_t reload_mgr_t::send(std::string& str)
{
	if (str.size() > MAX_PKG_SIZE) {
		std::cout << "Send Buff Size: " << str.size() << " Too Big Max_Pkg_len= " << 
			MAX_PKG_SIZE << std::endl;
		return -1;
	}
	memcpy(sendbuff, str.c_str(), str.size());
	sendlen = str.size();
	return sendto(mcast_fd_, sendbuff, sendlen, 0, 
			(sockaddr*)&mcast_addr_, sizeof mcast_addr_);
}

int32_t reload_mgr_t::send(const google::protobuf::Message* message)
{
	db_proto_header_t* header = (db_proto_header_t*)sendbuff;
	char* body = (sendbuff + sizeof(*header));
	int bodylen = 0;
	if (message) {
		if (!message->SerializeToArray(body, sizeof(sendbuff) - sizeof(*header))) {
			fprintf(stderr, "serialize failed\n");
			return -1;
		}
		bodylen = message->ByteSize();
		std::cout << "bodylen:" << bodylen << std::endl;
	}
	header->len = sizeof(*header) + bodylen;
	header->seq = 0;
	header->cmd = 0;
	header->ret = 0;
	header->uid = 0;
	if (sizeof(header) + bodylen > MAX_PKG_SIZE) {
		std::cout << "Send Buff Size: " << header->len << "Too Big,Max_pkg_len:" <<
			MAX_PKG_SIZE << std::endl;
		return -1;
	}
	std::cout << "Send Buff Size: " << header->len << std::endl;
	sendlen = header->len;
	return sendto(mcast_fd_, sendbuff, sendlen, 0,
			(sockaddr*)&mcast_addr_, sizeof mcast_addr_);
}

reload_mgr_t reload_mgr;

int main(int argc, char **argv)
{
	if (config_init("reload_conf.conf") == -1) {
		std::cout << "Reload_conf. File Not Found" << std::endl;
		return 0;
	}
	if (!reload_mgr.init(config_get_strval("mcast_ip"),
						config_get_intval("mcast_port", 0),
						config_get_strval("outgoing_ip"),
						config_get_strval("outgoing_interface"))) {
		std::cout << "Reload_mgr, init failed,mcast_ip: " << config_get_strval("mcast_ip")
				<< " mcast_port: " << config_get_intval("mcast_port", 0)
				<< " outgoing_ip: " << config_get_strval("outgoing_ip")
				<< " outgoing_interface: " << config_get_strval("outgoing_interface")
				<< std::endl;
		return 0;
	}
	/*
	google::ParseCommandLineFlags(&argc, &argv, true);
	if (FLAGS_conf_name.empty()) {
		std::cout << "必须给出 conf_name, 用 -conf_name=<nn> 指定" << std::endl;
		std::cout << "必须给出 server_id, 用 -server_id=<nn> 指定,0表示全部服务器加载" << std::endl;
		return -1;
	}
	*/
	std::string str_conf_name(argv[1]);
	std::string str_serverid(argv[2]);
	std::cout << "the str_conf_name=" << str_conf_name << ";serv_id=" << str_serverid << std::endl;
	reloadproto::mcast_reload_conf msg;
	msg.set_conf_name(str_conf_name);	
	uint32_t serverid = boost::lexical_cast<int32_t>(str_serverid);
	msg.set_serverid(serverid);

	reload_mgr.send(&msg);
}
