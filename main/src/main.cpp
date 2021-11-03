#include<iostream>
#include<vector>
#include<string.h>
#include <json/json.h>
#include "TestA.h"
#include "TestB.h"
#include <stdint.h>
#include <sys/time.h>
#include "InputControl.h"
#include<map>
#include "logic/CurlCommon.h"
#include <cmath>
#include<unordered_map>
#include<memory>
#include "socket/Socket.h"
#include <algorithm>
#include <thread>
#include "pthread.h"
#include "logic/KafkaConsumer.h"
#include "logic/KafkaProducer.h"
#include "logic/md5.h"
#include <memory>
#include "db/table_connect.h"
#include "db/CTable.h"
#include "db/CTableRoute100x10.h"
#include "db/CTableRoute100x100.h"

using namespace std;

int main(int argc,char **argv)	 
{
	char h[16] = "192.168.2.231";
	char u[16] = "inksg";
	char p[32] = "isg@mysql";
	std::shared_ptr<CTableConnect> g_db = std::make_shared<CTableConnect>(h,u,p);
	if(!g_db || !g_db->conn){
		cout << "init err" << endl;
		return 0;
	}
	
	std::shared_ptr<CTableRoute100x100> p_table = std::make_shared<CTableRoute100x100>(g_db,"EPLAN_ACCOUNT","test");
	if(p_table != nullptr){
		cout << "1: " << p_table->get_table_name() << endl;
		cout << "2: " << p_table->get_table_name(123456) << endl;
	}
	

	//char sql[128] = "insert into EPLAN_ACCOUNT.test (title) values('sdsd')";
	//g_db->execute_update_sql(sql);
	/*
	char sql[128] = "select title from EPLAN_ACCOUNT.test";
	MYSQL_RES* res = NULL;
	int ret = g_db->execute_query_sql(sql,&res);
	if(ret == 0){
		MYSQL_ROW row;
		while((row = mysql_fetch_row(res)) != NULL){
			cout << row[0] << endl;
		}

		mysql_free_result(res);
	}
	*/


	/*	
	PrintMap();
    while (1) {	
			if (InputControlMain()){ 
				//break; 
			}//当按下ESC时循环，ESC键的键值时27.
			PrintMap();
	}
*/	

	/*
	std::stringstream s;
	s << "7439a5b784f8155469243d72dcdc628c" << time(nullptr) << 1999999999999;
	std::cout << md5(s.str())  << "   len:" << strlen(md5(s.str().c_str()).c_str()) << endl;
	*/
	
	/*
	while(1){
		uint64_t a = 0;
		cout << "cin a num" << endl;
		cin >> a;
		std::stringstream str;
		str << a;
		cout << "a num is " << a << "len is " << strlen(str.str().c_str()) << endl;
	}
	*/
	/* 
	std::string server = "192.168.2.232:9092";
	std::string topic = "test";
	KafkaProducer* p_producer = new KafkaProducer();
	p_producer->init(server.c_str());
	p_producer->add_topic(topic);
	p_producer->produceMsg(topic,"Hello World!");


	std::string c_topic = "test_test";
	KafkaConsumer* p_consumer = new KafkaConsumer();
	p_consumer->init(server.c_str());
	p_consumer->consumer_msg(c_topic.c_str());
	*/
	/*
	pthread_t thread_id;
	p_a = new AS();
	p_a->a = 1;
	auto ret = pthread_create(&thread_id,NULL,printA,p_a);
	cout << ret << endl;
	delete p_a;
	p_a = nullptr;
	*/

/*	
	std::string ip = "127.0.0.1";
	std::shared_ptr<CSocket> p_server = std::make_shared<CSocket>();
	p_server->Init(ip,1234);
	p_server->Listen();
	
	std::shared_ptr<CSocket> p_client = std::make_shared<CSocket>();
	p_client->Init(ip,1234);
	p_client->Connect();


	thread s(&CSocket::AcceptData,p_server);
	s.detach();
	thread c(&CSocket::SendData,p_client);
	c.join();
*/

	/*
	// get 请求
	string strURL = "http://www.baidu.com";
	string strResponse;
	CURLcode nRes = CommonTools::HttpGet(strURL, strResponse,300);
	//size_t nSrcLength = strResponse.length();
	//cout << "aa:"  << nSrcLength << " Res:" << nRes << endl;
	if(nRes){

	}
	cout << "test:" << strResponse << endl;
	*/
	 

	return 0;
}
