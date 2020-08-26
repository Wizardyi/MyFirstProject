#include "utils.h"
#include <google/protobuf/util/json_util.h>
#include "global_data.h"
#include "RedisClient.hpp"

bool utils::set(const std::string& strKey, const google::protobuf::Message& msg)
{   
	std::string strValue;
    google::protobuf::util::MessageToJsonString(msg, &strValue);
    int err = redis_client->Set(strKey, strValue);
    if(err != RC_SUCCESS) {
        ERROR_LOG("redis set, error code:%d, key:%s, value:%s", 
                err, strKey.c_str(), strValue.c_str());
        return err;
    }
    return RC_SUCCESS;
}

bool utils::get(const std::string& strKey, google::protobuf::Message& msg)
{
    std::string strValue;
    int err = redis_client->Get(strKey, &strValue);
    if (err != RC_SUCCESS) {
        ERROR_LOG("redis get, error code:%d, key:%s", err, strKey.c_str());
        return err;
    }
    google::protobuf::util::JsonStringToMessage(strValue, &msg);
    return RC_SUCCESS;
}


bool utils::hset(const std::string& strKey, const std::string& strField, const google::protobuf::Message& msg)
{
    std::string strValue;
    google::protobuf::util::MessageToJsonString(msg, &strValue);
    int err = redis_client->Hset(strKey, strField, strValue);
    if(err != RC_SUCCESS) {
        ERROR_LOG("redis hset, error code:%d, key:%s, field:%s, value:%s",
                err, strKey.c_str(), strField.c_str(), strValue.c_str());
        return err;    
	}
    return RC_SUCCESS;
}

bool utils::hget(const std::string& strKey, const std::string& strField, google::protobuf::Message& msg)
{
    std::string strValue;
    int err = redis_client->Hget(strKey, strField, &strValue);
    if(err != RC_SUCCESS) {
        ERROR_LOG("redis hget, error code:%d, key:%s, field:%s, value:%s",
                err, strKey.c_str(), strField.c_str(), strValue.c_str());
        return err;
    }
    google::protobuf::util::JsonStringToMessage(strValue, &msg);
    return RC_SUCCESS;
}

/*
void utils::CheckSetAndGet(cacheproto::CreateRole &req,cacheproto::CreateRole &ack)
{
	std::stringstream str_key;
	str_key << "yzxtest:" << req.sourcenumber().c_str();
	utils::set(str_key.str(), req);

	std::stringstream str_key1;
	str_key1 << "yzxtest:" << req.sourcenumber().c_str();
	utils::get(str_key1.str(), ack);
}
*/
