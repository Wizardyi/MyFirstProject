#include "Socket.h"


void CSocket::Init(std::string& ip,int port)
{
	//创建套接字
	serv_sock_ = socket(AF_INET, SOCK_STREAM, 0);

	serv_addr_.sin_family = AF_INET;  //使用IPv4地址
	serv_addr_.sin_addr.s_addr = inet_addr(ip.c_str());  //具体的IP地址
	serv_addr_.sin_port = htons(port);  //端口
}

void CSocket::Listen()
{
	bind(serv_sock_, (struct sockaddr*)&serv_addr_, sizeof(serv_addr_));
	listen(serv_sock_, 10);
}


void CSocket::AcceptData()
{
	while(1)
	{
		memset(&clnt_addr_, 0, sizeof(clnt_addr_));
		uint32_t  addrlen = sizeof(clnt_addr_);
		//服务端阻塞等待客户端的连接 
		client_sock_ = accept(serv_sock_, (struct sockaddr*)&clnt_addr_, &addrlen);
		if(-1 == client_sock_)
		{
			perror("accept failed");
			return;
		}
		//string straddr = getaddr(cltaddr);
		string straddr = "aa";
		cout << "connect accept: " << endl;
		//客户端连接成功后 服务端接收客户端发来的一行消息 并打印到屏幕 
		while(1)
		{
			char buffer[100] = {0};
			int  recvlen     = 0;
			recvlen = recv(client_sock_, buffer, sizeof(buffer), 0);
			if(0 < recvlen)  //接收成功  
			{
				cout << "recv from " << straddr << " " << buffer;
			}
			else
			{
				cout << "client " << straddr <<" closed" << endl;
				break;
			}
		}
	}	
}


void CSocket::Connect()
{
	connect(serv_sock_, (struct sockaddr*)&serv_addr_, sizeof(serv_addr_));
}

void CSocket::SendData()
{
	cout << "connect success" << endl; 
	cout << "input: ";                 
	while(1)                           
	{                                  
		char c   = getchar();          
		int  len = 0;                  
		if('\n' == c)                  
		{                              
			cout << "input: ";         
		}                              
		len = send(serv_sock_, &c, 1, 0);
		if(len < 0)                    
		{                              
			break;                     
		}                              
	}               
}


