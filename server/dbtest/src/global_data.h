#pragma once
#include "server.h"
#include "logic/tables/testy.h"
#include "logic/tables/user_info.h"
#include "logic/tables/user_attr.h"
#include "proto_processor.h"
#include "logic/mysql/DBConn.h"

extern ProtoProcessor* processor;

extern CDBConn* g_db;
extern server_config_t g_config;

extern TestTable* g_test_table;
extern UserInfo*  g_user_info_table;
extern UserAttr*  g_user_attr_table;

