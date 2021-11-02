#include "KafkaProducer.h"
#include <sstream>

//发送回调函数
static void drMsgCb(rd_kafka_t *rk,const rd_kafka_message_t *rkmessage, void *opaque)
{
	if (rkmessage->err)
	{
		fprintf(stderr, "%% Message delivery failed: %s\n",rd_kafka_err2str(rkmessage->err));
		char buf[1024];
		int len = std::min(rkmessage->len,sizeof(buf));
		strncpy(buf,(char*)rkmessage->payload,len);
		buf[len] = 0;
	}
}

//错误回调函数
static int kfkErrorCode = 0;
static void errCb(rd_kafka_t *rk, int err, const char *reason, void *opaque)
{
	kfkErrorCode = err;
	std::stringstream str_err;
	str_err<<reason<<","<<opaque<<":"<<err<<"\r\n"<<rd_kafka_err2str((rd_kafka_resp_err_t)err);
	//cout << str_err << endl;
}


bool KafkaProducer::init(const char *server)
{
	if(_rk != nullptr || _topics.size() != 0 || _conf != nullptr)
	{
		return false;
	}

	//创建配置
	_conf = rd_kafka_conf_new();
	char errstr[512];
	if (rd_kafka_conf_set(_conf, "bootstrap.servers", server,errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK) {
		fprintf(stderr, "%s\n", errstr);
		return false;
	}
	//发送回调函数
	rd_kafka_conf_set_dr_msg_cb(_conf, drMsgCb);
	//错误回调函数
	rd_kafka_conf_set_error_cb(_conf,errCb);
	//初始化kafka
	_rk = rd_kafka_new(RD_KAFKA_PRODUCER, _conf, errstr, sizeof(errstr));
	if (!_rk) {
		fprintf(stderr,"%% Failed to create new producer: %s\n", errstr);
		return false;
	}

	//初始化一个默认的配置主题
	add_topic(_nomalTopic);

	std::cout << "init produce success!" << std::endl;
	return true;
}

bool KafkaProducer::add_topic(std::string& topic_name)
{
	if(_rk == nullptr || topic_name == ""){
		return false;
	}
	
	std::string topicstr = 	_nomalTopic;
	topicstr += "_";
	topicstr += topic_name;
	//创建主题
	rd_kafka_topic_t *temp_rkt = rd_kafka_topic_new(_rk,topicstr.c_str(), NULL);
	if (!temp_rkt)
	{
		return false;
	}

	_topics.emplace(std::make_pair(topic_name,temp_rkt));

	std::cout << "add topic " << topic_name << " success!" << std::endl;

	return true;
}



void KafkaProducer::produceMsg(const std::string &topic,const char *msg)
{
	if(_rk == nullptr || _topics.size() == 0 || _conf == nullptr)
	{
		return;                                                
	}                                                          

	auto iter = _topics.find(topic);
	if(iter == _topics.end()){
		//使用默认主题
		std::cout << "aaaaaaa" << std::endl;
		iter = _topics.find(_nomalTopic);
	}
	
	if(iter == _topics.end()){
		return;
	}

retry:
	//调用生产者接口
	int len = strlen(msg);
	if (rd_kafka_produce(iter->second,RD_KAFKA_PARTITION_UA,RD_KAFKA_MSG_F_COPY,(void*)msg, len,NULL, 0,NULL) == -1)
	{
		fprintf(stderr,"%% Failed to produce to topic %s: %s\n",
				rd_kafka_topic_name(iter->second),
				rd_kafka_err2str(rd_kafka_last_error()));
	
		if(rd_kafka_last_error() == RD_KAFKA_RESP_ERR__QUEUE_FULL){
			 /*如果内部队列满，等待消息传输完成并retry, 
			   内部队列表示要发送的消息和已发送或失败的消息， 
			   内部队列受限于queue.buffering.max.messages配置项*/ 
			rd_kafka_poll(_rk, 10);
			goto retry;
		}
	
	}

	std::cout << topic << " produce msg success!" << std::endl;
	//阻塞等待消息发送完成
	rd_kafka_poll(_rk, 10);

}

