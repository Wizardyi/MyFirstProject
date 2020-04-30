#include "service.h"
#include "share/module/proto.h"
#include "timer_procs.h"

Service::Service(const std::string& service_name)
{
    service_name_ = service_name;
    fd_ = -1;
}

Service::~Service()
{
    if (fd_ >= 0) {
        close_svr(fd_);
    }
}

int Service::send_buf(uint32_t userid, uint16_t cmd, uint32_t seq,
        const char* body, int bodylen)
{
    if (fd_ < 0) {
        ERROR_LOG("service '%s' not available", service_name_.c_str());    
        return -1;
    }

    db_proto_header_t* header = (db_proto_header_t* )send_buf_;

    if (!body || bodylen < 0) {
        bodylen = 0; 
    }

    header->len = sizeof(*header) + bodylen;
    header->seq = seq;
    header->cmd = cmd;
    header->ret = 0;
    header->uid = userid;   //uid存放操作db的uid

    if (bodylen) {
        memcpy(send_buf_ + sizeof(*header), body, bodylen);
    }

    int ret = net_send(fd_, send_buf_, header->len);

    if (ret != 0) {
        ERROR_LOG("net_send to service '%s' failed", 
                service_name_.c_str());
        return -1; 
    }

    TRACE_LOG("Send Buf To Service Ok: [u:%u cmd:%u hex_cmd:0x%04X service:%s]",
            userid, cmd, cmd, service_name().c_str());
    return 0;
}

int Service::send_msg(uint32_t userid, uint16_t cmd, uint32_t seq,
        const google::protobuf::Message& message)
{
    if (fd_ < 0) {
        ERROR_LOG("service '%s' not available", service_name_.c_str());    
        return -1;
    }

    db_proto_header_t* header = (db_proto_header_t* )send_buf_;

    header->len = sizeof(*header) + message.ByteSize();
    header->seq = seq;
    header->cmd = cmd;
    header->ret = 0;
    header->uid = userid;

    if (header->len > sizeof(send_buf_)) {
        ERROR_LOG("too large pkg size %u cmd %u send to '%s'",
                header->len, cmd, service_name_.c_str()); 
        return -1;
    }

    if (!message.SerializePartialToArray(
            send_buf_ + sizeof(*header), 
            sizeof(send_buf_) - sizeof(*header))) {
        ERROR_LOG("serialize message 0x'%04x' failed", cmd);
        return -1;
    }

    int ret = net_send(fd_, send_buf_, header->len);

    if (ret < 0) {
        ERROR_LOG("net_send to service '%s' failed", 
                service_name_.c_str());
        return -1; 
    }

    TRACE_LOG("Send Msg To Service Ok: [u:%u cmd:%u hex_cmd:0X%04X service:%s]\nmsg:%s\n[%s]",
            userid, cmd, cmd, service_name().c_str(),
            message.GetTypeName().c_str(), message.Utf8DebugString().c_str());
    DEBUG_LOG("Send Msg To Service Ok: [u:%u cmd:%u hex_cmd:0X%04X service:%s]\nmsg:%s\n[%s]",
            userid, cmd, cmd, service_name().c_str(),
            message.GetTypeName().c_str(), message.Utf8DebugString().c_str());

    return 0;
}

int Service::send_cmsg(uint32_t userid, uint16_t cmd,
        uint32_t seq, Cmessage *msg)
{
    if (fd_ < 0) {
        KERROR_LOG(0, "service '%s' not available", service_name_.c_str());    
        return -1;
    }

	db_proto_header_t header;

	header.len = sizeof(header);
	header.seq = seq;
	header.cmd = cmd;
	header.ret = 0;
	header.uid = userid;

TRACE_LOG("Send CMsg To Service Ok: [u:%u cmd:%u cmd:0X%04X service:%s]",
            userid, cmd, cmd, service_name().c_str());

	return net_send_msg(fd_, (char *)&header, msg);
}

int Service::send_cmd(uint16_t cmd, uint32_t uid)
{
	if (fd_ < 0) {
		ERROR_LOG("service '%s' not available", service_name_.c_str());
		return -1;
	}

	db_proto_header_t* header = (db_proto_header_t*)send_buf_;
	header->len = sizeof(*header);
	header->seq = 0;
	header->cmd = cmd;
	header->uid = uid;

	int err = net_send(fd_, send_buf_, header->len);
	if (err < 0) {
		ERROR_LOG("net_send to service '%s' failed", service_name_.c_str());
		return -1;
	}

	return 0;
}

int Service::close()
{
    fd_ = -1;

    return 0;
}

void Service::on_connect_callback(int fd, void* args)
{
    Service* service = (Service *)args;

    DEBUG_LOG("on connect callback");

    if (fd > 0) {
        DEBUG_LOG("connect to service %s OK",
                service->service_name().c_str());
        service->set_fd(fd);
    } else {
        ERROR_LOG("connect to service %s Failed", 
                service->service_name().c_str());

        ADD_TIMER_EVENT_EX(&g_reconnect_timer, 
                kTimerTypeReconnectServiceTimely, 
                service, 
                get_now_tv()->tv_sec + kTimerIntervalReconnectServiceTimely);

		asynsvr_send_warning_msg("ConnErr", 0, 0, 0, service->service_name().c_str());
    }
}

int Service::connect()
{
    return asyn_connect_to_service(service_name_.c_str(), 0,
            65536, Service::on_connect_callback, this);    
}
