#ifndef __CONN_MANAGER_H_
#define __CONN_MANAGER_H_

#include "share/module/common.h"
#include "share/module/proto.h"

#define IP_SIZE (16)
#define ONLINE_KEEPLIVE_INTERVAL (70)

#pragma pack(push,1)

// 该文件定义的接口操作的是本服务对其他服务发起的连接

#ifdef CLIENT
int send_err_to_fdsess(
		const fdsession_t *fdsess, uint32_t uid, uint32_t cmd, uint32_t seq, uint32_t ret);

int send_err_to_conn(cli_proto_header_t* header, fdsession_t* fdsess, uint32_t ret);

int send_msg_to_conn(
		cli_proto_header_t* header, fdsession_t* fdsess, const google::protobuf::Message& msg);

int send_msg_to_conn_ex(cli_proto_header_t* header,
		uint32_t cmd, uint32_t target_uid,
		fdsession_t* fdsess,
		const google::protobuf::Message& msg);

#else
int send_err_to_fdsess(
		const fdsession_t *fdsess, uint32_t uid, uint32_t cmd, uint32_t seq, uint32_t ret);

int send_err_to_conn(db_proto_header_t* header, fdsession_t* fdsess, uint32_t ret);

int send_msg_to_conn(
		db_proto_header_t* header, fdsession_t* fdsess, const google::protobuf::Message& msg);

int send_msg_to_conn_ex(db_proto_header_t* header,
		uint32_t cmd, uint32_t target_uid,
		fdsession_t* fdsess,
		const google::protobuf::Message& msg);
#endif
#pragma pack(pop)

#endif
