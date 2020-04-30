#include "conn_manager.h"
#include "share/config/size_df.h"

#ifdef CLIENT
int send_err_to_fdsess(
		const fdsession_t *fdsess, uint32_t uid, uint32_t cmd, uint32_t seq, uint32_t ret)
{                  
    char send_buf[20] = {0};	
    cli_proto_header_t* header = (cli_proto_header_t *)send_buf;

    header->len = sizeof(*header);
    header->seq = seq;
    header->cmd = cmd;
    header->ret = ret;
    header->checksum = 0;

    DEBUG_LOG("Send Err To Fd: [fd:%d, u:%u, cmd:%u, hex_cmd:0x%04X, err:%u]",
            fdsess->fd, uid, cmd, cmd, ret);

    return send_pkg_to_client((fdsession_t*)fdsess, send_buf, header->len);
}

int send_err_to_conn(cli_proto_header_t* header, fdsession_t* fdsess, uint32_t ret)
{
	char send_buf[20] = {0};
    assert(fdsess);

    cli_proto_header_t* db_header = (cli_proto_header_t *)send_buf;

    db_header->len = sizeof(*db_header);
    db_header->seq = header->seq;
    db_header->cmd = header->cmd;
    db_header->ret = ret;
    db_header->checksum = 0;

    DEBUG_LOG("Send ERR TO Conn[cmd:%u, hex_cmd:0x%04X, ret:%d]",
            header->cmd, header->cmd, ret);

    send_pkg_to_client(fdsess, send_buf, db_header->len);
    return 0;
}


int send_msg_to_conn(
		cli_proto_header_t* header, fdsession_t* fdsess, const google::protobuf::Message& msg)
{
	char send_buf[OL_TO_CLI_MAX_LEN] = {0}; 
    assert(fdsess);

    cli_proto_header_t *db_header = (cli_proto_header_t *)(send_buf);

    if (sizeof(send_buf) < sizeof(*header) + msg.ByteSize()) {
        ERROR_LOG("send buf size %lu not enough proto %lu",
                sizeof(send_buf), sizeof(*header) + msg.ByteSize());
        return -1;
    }

    msg.SerializeToArray(send_buf + sizeof(*db_header), sizeof(send_buf) - sizeof(*db_header));

    db_header->len = sizeof(*db_header) + msg.ByteSize();
    db_header->seq = header->seq;
    db_header->cmd = header->cmd;
    db_header->ret = 0;

	DEBUG_LOG("Send Msg To Conn: [cmd:%d, hex_cmd:0x%04X, msg:%s\n[%s]",
			header->cmd, header->cmd,
			msg.GetTypeName().c_str(),
			msg.Utf8DebugString().c_str());

    send_pkg_to_client(fdsess, send_buf, db_header->len);
    return 0;
}

int send_msg_to_conn_ex(cli_proto_header_t* header,
		uint32_t cmd, uint32_t target_uid,
		fdsession_t* fdsess,
		const google::protobuf::Message& msg)
{
	header->cmd = cmd;	
	return send_msg_to_conn(header, fdsess, msg);
}


#else
int send_err_to_fdsess(
		const fdsession_t *fdsess, uint32_t uid, uint32_t cmd, uint32_t seq, uint32_t ret)
{                  
    char send_buf[18] = {0};	
    db_proto_header_t* header = (db_proto_header_t *)send_buf;

    header->len = sizeof(*header);
    header->seq = seq;
    header->cmd = cmd;
    header->ret = ret;
    header->uid = uid;

    DEBUG_LOG("Send Err To Fd: [fd:%d, u:%u, cmd:%u, hex_cmd:0x%04X, err:%u]",
            fdsess->fd, uid, cmd, cmd, ret, header->len);

    return send_pkg_to_client((fdsession_t*)fdsess, send_buf, header->len);
}

int send_err_to_conn(db_proto_header_t* header, fdsession_t* fdsess, uint32_t ret)
{
	char send_buf[18] = {0};
    assert(fdsess);

    db_proto_header_t* db_header = (db_proto_header_t *)send_buf;

    db_header->len = sizeof(*db_header);
    db_header->seq = header->seq;
    db_header->cmd = header->cmd;
    db_header->ret = ret;
    db_header->uid = header->uid;

    DEBUG_LOG("Send ERR TO Conn[cmd:%u, hex_cmd:0x%04X, uid:%u, ret:%d]",
            header->cmd, header->cmd, header->uid, ret);

    send_pkg_to_client(fdsess, send_buf, db_header->len);
    return 0;
}


int send_msg_to_conn(
		db_proto_header_t* header, fdsession_t* fdsess, const google::protobuf::Message& msg)
{
	char send_buf[SVR_TO_OL_MAX_LEN] = {0}; 
    assert(fdsess);

    db_proto_header_t *db_header = (db_proto_header_t *)(send_buf);

    if (sizeof(send_buf) < sizeof(*header) + msg.ByteSize()) {
        ERROR_TLOG("send buf size %lu not enough proto %lu",
                sizeof(send_buf), sizeof(*header) + msg.ByteSize());
        return -1;
    }

    msg.SerializeToArray(send_buf + sizeof(*db_header), sizeof(send_buf) - sizeof(*db_header));

    db_header->len = sizeof(*db_header) + msg.ByteSize();
    db_header->seq = header->seq;
    db_header->cmd = header->cmd;
    db_header->ret = 0;
    db_header->uid = header->uid;

	DEBUG_LOG("Send Msg To Conn: [cmd:%d, hex_cmd:0x%04X, uid:%u, msg:%s\n[%s]",
			header->cmd, header->cmd, header->uid,
			msg.GetTypeName().c_str(),
			msg.Utf8DebugString().c_str());

    send_pkg_to_client(fdsess, send_buf, db_header->len);
    return 0;
}

int send_msg_to_conn_ex(db_proto_header_t* header,
		uint32_t cmd, uint32_t target_uid,
		fdsession_t* fdsess,
		const google::protobuf::Message& msg)
{
	header->cmd = cmd;	
	header->uid = target_uid;
	return send_msg_to_conn(header, fdsess, msg);
}

#endif
