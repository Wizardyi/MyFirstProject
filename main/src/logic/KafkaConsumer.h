#pragma once
#include <librdkafka/rdkafka.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>
#include <string.h>

using namespace std;

class KafkaConsumer
{
	public:
		KafkaConsumer(){
			_rk = nullptr;
			_conf = nullptr;
			topics = nullptr;
		}
		~KafkaConsumer(){
			if(_conf != nullptr)            
			{
				rd_kafka_conf_destroy(_conf);
				_conf = nullptr;            
			}                               
			if(_rk != nullptr)              
			{
				rd_kafka_destroy(_rk);      
				_rk = nullptr;              
			}                               
		
			if(topics != nullptr){
				rd_kafka_topic_partition_list_destroy(topics);
			}
		

		}

		//初始化
		//server : kafka的ip端口
		bool init(const char *server);
		
		bool consumer_msg(const char *topic);

	private:
		rd_kafka_t *_rk;        //kafka句柄
		rd_kafka_conf_t *_conf; //配置
		rd_kafka_topic_partition_list_t *topics; //监听列表
		rd_kafka_topic_conf_t *topic_conf; //主题配置
		rd_kafka_resp_err_t err; //请求错误
		
};



