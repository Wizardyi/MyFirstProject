#ifndef __PROTO_H_
#define __PROTO_H_

#include <stdint.h>
// #include "share/err.h"

struct cli_proto_header_t
{
    uint32_t len;
    uint32_t seq;
    uint32_t cmd;
    uint32_t ret;
    uint32_t checksum;
} __attribute__((packed));

struct db_proto_header_t
{
    uint32_t len;   
    uint32_t seq;
    uint16_t cmd;
    uint32_t ret;
    uint32_t uid;
} __attribute__((packed));

struct db_is_active_req_t
{
    uint8_t gameid;
} __attribute__((packed));

struct db_is_active_ack_t
{
    uint8_t is_active;
} __attribute__((packed));

struct db_add_session_req_t
{
    uint32_t gameid; 
    uint32_t ip;
} __attribute__((packed));

struct db_add_session_ack_t
{
    char session[16];
} __attribute__((packed));

struct db_check_session_req_t
{
    uint32_t from_game;
    char session[16];
    uint32_t del_flag;
    uint32_t to_game;
    uint32_t ip;
    uint16_t region;
    uint8_t enter_game;
    char tad[128];
} __attribute__((packed));

struct db_user_logout_req_t
{
    uint32_t gameid; 
    uint32_t login_time;
    uint32_t logout_time;
} __attribute__((packed));

struct db_login_with_verify_code_req_t
{
    char email[64];
    char passwd_md5_two[16];
    uint16_t verifyid;
    uint16_t region;
    uint16_t gameid;
    uint32_t ip;
    char verify_session[16];
    char verify_code[6];
    uint16_t login_channel;
    char login_promot_tag[128];
} __attribute__((packed));

#define DB_LOGIN_ACK_FLAG_SUCC 0
#define DB_LOGIN_ACK_FLAG_WRONG_PASSWD_TOO_MUCH 1
#define DB_LOGIN_ACK_FLAG_LOGIN_IN_DIFF_CITY 2
#define DB_LOGIN_ACK_FLAG_LOGIN_IN_DIFF_CITY_TOO_MUCH 3
#define DB_LOGIN_ACK_FLAG_WRONG_VERIFY_CODE 4
#define DB_LOGIN_ACK_FLAG_ACCOUNT_UNSAFE 5

struct db_login_with_verify_code_ack_t
{
    uint32_t flag; 
} __attribute__((packed));

struct db_get_boss_info_req_t
{
    uint8_t gameid; 
    uint32_t query_count;
    uint32_t start_time;
    uint32_t end_time;
} __attribute__((packed));

struct db_get_boss_info_ack_t
{
    uint32_t query_count; 
    uint32_t consume_num;
} __attribute__((packed));


struct db_get_gameflag_ack_t
{
    uint32_t gameflag;
} __attribute__((packed));

#endif
