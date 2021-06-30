#pragma once
#include<stdlib.h>
#include<memory>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<iostream>
#include<string.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;

#define BUFF_SIZE 1024*100

class CSocket
{
	public:
		CSocket(){
			memset(&serv_addr_, 0, sizeof(serv_addr_));
			memset(&clnt_addr_, 0, sizeof(clnt_addr_));
		}

		~CSocket(){

		}

		//初始化
		void Init(std::string& ip,int port);
		//监听
		void Listen();

		//建立链接
		void Connect();

		//接收数据
		void AcceptData();

		//发送数据
		void SendData();

	private:
		int serv_sock_;//服务器套接字
		int client_sock_;//客户端套接字
		struct sockaddr_in serv_addr_;
		struct sockaddr_in clnt_addr_;
		char buffer[BUFF_SIZE];//缓存区
};



