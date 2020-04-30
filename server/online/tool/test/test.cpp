
#include <stdint.h>
#include <google/protobuf/message.h>
#include <iostream>
#include <vector>
extern "C" {
#include <libtaomee/inet/tcp.h>
}
#include  <libtaomee++/utils/strings.hpp>

#include "proto.h"
#include "../../../proto/online/online.pb.h"
#include "../../../proto/online/player.pb.h"
#include "../share/cmd.h"
#include "../share/EncodeDecode.h"

static char buf[409600];
static char hex_buf[409600];

static uint32_t seq = 1;

int test_send(int fd, uint32_t cmd, uint32_t userid,
        google::protobuf::Message* message)
{
    cli_proto_header_t* header = (cli_proto_header_t *)buf;
    // db_proto_header_t* header = (db_proto_header_t *)buf;
    char* body = (buf + sizeof(*header));
    int bodylen = 0;

    if (message) {
        if (!message->SerializeToArray(body, 
                    sizeof(buf) - sizeof(*header))) {
            fprintf(stderr, "serialize failed\n");
            return -1;
        }
        bodylen = message->ByteSize();
    }

	EncodeBufSimple(bodylen, (unsigned char *)body);

    header->len = sizeof(*header) + bodylen;
    header->seq = seq++;
    header->cmd = cmd;
    header->ret = 0;
	header->checksum = userid;
	// header->uid = userid;

    int n_send = safe_tcp_send_n(fd, buf, header->len);

    if (n_send == -1) {
        fprintf(stderr, "send failed\n"); 
        return -1;
    } else if (n_send != header->len) {
        fprintf(stderr, "send %d, expect %u\n",
                n_send, header->len); 
        return -1;
    }

	memset(hex_buf, 0, sizeof(hex_buf));
	bin2hex(hex_buf, buf, n_send);
	fprintf(stdout, "send buf: %s\n", hex_buf);

    return 0;
}

int test_recv(int fd, 
        google::protobuf::Message* message, uint32_t& recv_cmd)
{
    cli_proto_header_t* header = (cli_proto_header_t *)buf;
    // db_proto_header_t* header = (db_proto_header_t *)buf;
    int n_recv = safe_tcp_recv_n(fd, header, sizeof(*header));

    if (n_recv == 0) {
        fprintf(stderr, "closed by server\n");
        return -1; 
    }

    fprintf(stdout, "recv header %d size\n", n_recv);
    fprintf(stdout, "len: %u, seq: %u, cmd: %u, ret: %u\n",
            header->len, header->seq, header->cmd, header->ret);

	recv_cmd = header->cmd;
    int bodylen = header->len - sizeof(*header);

    if (bodylen > 0) {

        n_recv = safe_tcp_recv_n(fd, buf, bodylen);

        if (n_recv == 0) {
            fprintf(stderr, "closed by server\n"); 
            return -1;
        }

        fprintf(stdout, "recv body %d size\n", n_recv);

	//	if (recv_cmd != send_cmd) {
	//		return n_recv;
	//	}

        if (n_recv != bodylen) {
            fprintf(stderr, "recv unexpect body len %d, expect %d\n",
                    n_recv, bodylen);             
            return -1;
        }

        memset(hex_buf, 0, sizeof(hex_buf));
        bin2hex(hex_buf, buf, n_recv);
        fprintf(stdout, "recv buf: %s\n", hex_buf);

        if (message) {
            if (!message->ParseFromArray(buf, n_recv)) {
                fprintf(stderr, "parse message failed\n"); 
                return -1;
            }
			
			puts("--ack--");
			// print_fields(*ack); 
			printf("msg:%s\n[%s]", 
					message->GetTypeName().c_str(), message->Utf8DebugString().c_str());
			puts("--ack--");
			fprintf(stdout, "------test cmd %04x(%u) OK------\n\n\n", recv_cmd, recv_cmd);
        }
    }

	return n_recv;
}

int print_fields(const google::protobuf::Message& msg)
{
    const google::protobuf::Reflection * msg_reflect = msg.GetReflection();
    std::vector<const google::protobuf::FieldDescriptor *> fields;
    msg_reflect->ListFields(msg, &fields);

    std::vector<const google::protobuf::FieldDescriptor *>::iterator it = fields.begin();

    for (it = fields.begin(); it != fields.end(); it++) {
        std::cout << (*it)->name() << " = ";

        switch ((*it)->type()) {
            case google::protobuf::FieldDescriptor::TYPE_INT32:
                std::cout << msg_reflect->GetInt32(msg, *it) << std::endl;
                break;
            case google::protobuf::FieldDescriptor::TYPE_UINT32:
                std::cout << msg_reflect->GetUInt32(msg, *it) << std::endl;
                break;  
            case google::protobuf::FieldDescriptor::TYPE_INT64:
                std::cout << msg_reflect->GetInt64(msg, *it) << std::endl;
                break;
            case google::protobuf::FieldDescriptor::TYPE_UINT64:
                std::cout << msg_reflect->GetUInt64(msg, *it) << std::endl;
                break;
            case google::protobuf::FieldDescriptor::TYPE_STRING:
                std::cout << msg_reflect->GetString(msg, *it) << std::endl;
                break;
            case google::protobuf::FieldDescriptor::TYPE_ENUM:
                std::cout << (msg_reflect->GetEnum(msg, *it)) << std::endl;
                break;    
            case google::protobuf::FieldDescriptor::TYPE_BOOL:
                std::cout << (msg_reflect->GetBool(msg, *it)) << std::endl;
                break;
           //  case google::protobuf::FieldDescriptor::TYPE_MESSAGE:
           //     print_fields(msg_reflect->GetMessage(msg, *it));
           //     break;
        }

    }

    return 0;
}

int test(int fd, uint32_t m_send_cmd, uint32_t m_recv_cmd, uint32_t userid, 
        google::protobuf::Message* req, 
        google::protobuf::Message* ack)
{
    fprintf(stdout, "------start test cmd 0x%04x(%u)------\n", m_send_cmd, m_send_cmd);

    if (req) {
        printf("---req---\n");
        // print_fields(*req);
		printf("msg:%s\n[%s]", req->GetTypeName().c_str(), req->Utf8DebugString().c_str());
        printf("---req---\n");
    }

    if (test_send(fd, m_send_cmd, userid, req) == -1) {
        return -1; 
    }

	uint32_t recv_cmd = 0;
	int ret = test_recv(fd, ack, recv_cmd);
	while (recv_cmd != m_recv_cmd) {
		ret = test_recv(fd, ack, recv_cmd);
	}

   //  if (test_recv(fd, ack) == -1) {
   //      return -1; 
   //  }

    return 0;
}

