#pragma once
#include <librdkafka/rdkafka.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>
#include <string.h>

using namespace std;

class KafkaProducer
{
	public:
		KafkaProducer(){
			_rk = nullptr;
			_conf = nullptr;
			_nomalTopic = "test";
			_topics.clear();
		}
		~KafkaProducer(){
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

			/*
			auto iter = _topics.begin();
			for(;iter != _topics;iter++)
			{
				rd_kafka_topic_destroy(*iter->second);
			}*/

			_topics.clear();
		}

		//初始化
		//server : kafka的ip端口
		bool init(const char *server);
		
		//添加主题
		//topic_name : 主题名字
		bool add_topic(std::string& topic_name);
		
		//生产数据
		void produceMsg(const std::string &topic,const char *msg);


	private:
		rd_kafka_t *_rk;        //kafka句柄
		rd_kafka_conf_t *_conf; //配置

		std::string _nomalTopic;    //默认主题
		//主题配置
		std::unordered_map<std::string,rd_kafka_topic_t*> _topics;
		
};



