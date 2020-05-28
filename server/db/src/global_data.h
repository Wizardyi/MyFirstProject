#pragma once
#include "server.h"
#include "logic/tables/testy.h"
#include "proto_processor.h"


extern ProtoProcessor* processor;

extern mysql_interface* g_db;
extern server_config_t g_config;

extern TestTable* g_test_table;


