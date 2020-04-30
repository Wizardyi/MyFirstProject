
#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <google/protobuf/message.h>

int test(int fd, uint32_t m_send_cmd, uint32_t m_recv_cmd, uint32_t userid, 
        google::protobuf::Message* req, 
        google::protobuf::Message* ack);

#define EXPECT(exp1, exp2) \
    do { \
        int v1 = exp1; \
        int v2 = exp2; \
        if (v1 != v2) { \
            fprintf(stderr, "exp1 '%s' = %d not equal to exp2 '%s' = %d\n", \
                #exp1, v1, #exp2, v2);\
            exit(EXIT_FAILURE); \
        } \
    } while (0)

#define PRINT_EXP(exp) \
    do { \
        std::cout << "exp '" << #exp << "' = " << exp << std::endl;\
    } while (0)

#endif
