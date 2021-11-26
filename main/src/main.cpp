#include<iostream>
#include<vector>
#include<string.h>
//#include <json/json.h>
#include "TestA.h"
#include "TestB.h"
#include <stdint.h>
#include <sys/time.h>
#include "InputControl.h"
#include<map>
//#include "logic/CurlCommon.h"
#include <cmath>
#include<unordered_map>
#include<memory>
#include "socket/Socket.h"
#include <algorithm>
#include <thread>
#include "pthread.h"
//#include "logic/KafkaConsumer.h"
//#include "logic/KafkaProducer.h"
#include "logic/md5.h"
#include <memory>
#include "db/table_connect.h"
#include "db/CTable.h"
#include "db/CTableRoute100x10.h"
#include "db/CTableRoute100x100.h"
#include "./algorithm/test_fun.h"
#include "Design/Factory.h"
#include "Design/AbstractFactory.h"
#include "Design/Singleton.h"
#include "Design/DecoratorPattern.h"

using namespace std;

int main(int argc,char **argv)	 
{

#if 0
	Circle* circle = new Circle();
	ShapeDecorator* redCircle = new RedShapeDecorator(new Circle());
	ShapeDecorator* redRectangle = new RedShapeDecorator(new Rectangle());
	circle->draw();
	redCircle->draw();
	redRectangle->draw();

	delete circle;
	delete redCircle;
	delete redRectangle;

#endif


#if 0
	
	//单例模式
	auto p = Singleton::GetInstance();

	//工厂模式
	//抽象工厂模式
	
	//初始化抽象工厂
	auto p_factory = std::make_shared<CAbstractFactory>();

	//获得工厂1
	auto p_f1 = p_factory->GetFactory(1);
	if(p_f1){
		//生成产品1
		auto p1 = p_f1->GetProduct(1);
		cout << "bbb" << endl;
		if(p1){
			cout << "aaa" << endl;
			p1->Print();
		}

		//生成产品2
		auto p2 = p_f1->GetProduct(2);
		if(p2){
			p2->Print();
		}
	}
	//获得工厂2
	auto p_f2 = p_factory->GetFactory(2);
	if(p_f2){
		//生成产品1
		auto p1 = p_f2->GetProduct(1);
		if(p1){
			p1->Print();
		}

		//生成产品2
		auto p2 = p_f2->GetProduct(2);
		if(p2){
			p2->Print();
		}


	}
#endif

#if 0	
	std::string a,b;
	stack<char> build;
		vector<char> operate;

	cout << "cin a and b" << endl;
	cin >> a >> b;
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	TestFun::dfs(0,0,a,b,build,operate);
	cout << "----------" << endl;
#endif

#if 0
	//db相关逻辑
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
	

	char sql[128] = "insert into EPLAN_ACCOUNT.test (title) values('sdsdaa')";
	g_db->execute_update_sql(sql);
	//mysql_commit(g_db->conn);
	mysql_rollback(g_db->conn);
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

#endif

#if 1	
	PrintMap();
    while (1) {	
			if (InputControlMain()){ 
				break; 
			}//当按下ESC时循环，ESC键的键值时27.
			PrintMap();
	}
#endif 

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
