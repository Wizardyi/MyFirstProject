#include "KafkaConsumer.h"
#include <sstream>

static void msg_consume (rd_kafka_message_t *rkmessage,  
		void *opaque) {  
	if (rkmessage->err) {  
		std::cout << "rkmessage->err :" << rkmessage->err << endl;
		//return;  
	}  

	std::cout << "rd_kafka_topic_name: " << rd_kafka_topic_name(rkmessage->rkt) << endl
		<< "rkmessage->partition: " <<	rkmessage->partition << endl
		<< "rkmessage->offset: " << rkmessage->offset << endl
		<< "rkmessage->len: "<< rkmessage->len  << endl;

	if (rkmessage->key_len) {  
		printf("Key: %.*s\n",  
				(int)rkmessage->key_len, (char *)rkmessage->key);  
	}  

	printf("%.*s\n",  
			(int)rkmessage->len, (char *)rkmessage->payload);  

}  


bool KafkaConsumer::init(const char *server)
{
	if(_rk != nullptr || _conf != nullptr)
	{
		return false;
	}

	char tmp[16];
	//创建配置
	_conf = rd_kafka_conf_new();
	char errstr[512];

	rd_kafka_conf_set(_conf, "nternal.termination.signal", tmp,NULL,0);
	
	topic_conf = rd_kafka_topic_conf_new();

	if(!server){
		server = "rdkafka_consumer_example";
	}
	
	if(rd_kafka_conf_set(_conf, "group.id", server,errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK){
		fprintf(stderr, "%s\n", errstr);
		return false;                   
	}

	if (rd_kafka_topic_conf_set(topic_conf, "offset.store.method","broker",errstr, sizeof(errstr)) !=  RD_KAFKA_CONF_OK) {
		fprintf(stderr, "%% %s\n", errstr);  
		return -1;  
	}  

	 rd_kafka_conf_set_default_topic_conf(_conf, topic_conf);

	
	//初始化kafka
	_rk = rd_kafka_new(RD_KAFKA_CONSUMER, _conf, errstr, sizeof(errstr));
	if (!_rk) {
		fprintf(stderr,"%% Failed to create new consumer: %s\n", errstr);
		return false;
	}

	if (rd_kafka_brokers_add(_rk, server) == 0){
		fprintf(stderr, "%% No valid brokers specified\n");  
		return -1;  
	}  


	return true;
}


bool KafkaConsumer::consumer_msg(const char *topic)
{
	if(_rk == nullptr || topic_conf == nullptr){
		return false;
	}


	//重定向 rd_kafka_poll()队列到consumer_poll()队列  
	rd_kafka_poll_set_consumer(_rk);  

	//创建一个Topic+Partition的存储空间(list/vector)  
	topics = rd_kafka_topic_partition_list_new(1);  
	//把Topic+Partition加入list  
	rd_kafka_topic_partition_list_add(topics, topic, -1);  
	//开启consumer订阅，匹配的topic将被添加到订阅列表中  
	if((err = rd_kafka_subscribe(_rk, topics))){  
		fprintf(stderr, "%% Failed to start consuming topics: %s\n", rd_kafka_err2str(err));  
		return false;  
	}  	

	auto rkmessage = rd_kafka_consumer_poll(_rk, 1000);
	if(rkmessage){  
        msg_consume(rkmessage, NULL);
        /*释放rkmessage的资源，并把所有权还给rdkafka*/  
        rd_kafka_message_destroy(rkmessage);  
      }

	return true;
}


