#pragma once
#include "winsock2.h"
#include <stdio.h>
#include <iostream>
using namespace std;

#pragma comment(lib,"ws2_32.lib")

void main(){

	//初始化Winsock环境
	freopen("./config.txt", "r", stdin);
	WSADATA wsaData;
	fd_set rfds;				//用于检查socket是否有数据到来的的文件描述符，用于socket非阻塞模式下等待网络事件通知（有数据到来）
	fd_set wfds;				//用于检查socket是否可以发送的文件描述符，用于socket非阻塞模式下等待网络事件通知（可以发送数据）
	bool first_connetion = true;

	int nRc = WSAStartup(0x0202,&wsaData);

	if(nRc){
		cout<<"Winsock  startup failed with error!\n";
	}

	if(wsaData.wVersion != 0x0202){
		cout << "Winsock version is not correct!\n";
	}

	cout << "Winsock  startup Ok!\n";

	//配置监听地址、监听端口和主目录 
	

	sockaddr_in clientAddr;
	SOCKET sessionSocket;

	//create socket
	SOCKET srvSocket = socket(AF_INET,SOCK_STREAM,0);
	if(srvSocket != INVALID_SOCKET)
		printf("Socket create Ok!\n");

	//set port and ip
	int port;
	string inaddr, main_directory;
	cout << "please enter port:\n";
	cin >> port;
	cout << "please enter inaddr:\n";
	cin >> inaddr;
	cout << "please enter main_directory:\n";
	cin >> main_directory;

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr(inaddr.c_str());

	//binding
	int rtn = bind(srvSocket,(LPSOCKADDR)&addr,sizeof(addr));
	if(rtn != SOCKET_ERROR)
		cout << "Socket bind Ok!\n";
	//listen
	rtn = listen(srvSocket,5);
	if(rtn != SOCKET_ERROR)
		cout << "Socket listen Ok!\n";

	clientAddr.sin_family =AF_INET;
	int addrLen = sizeof(clientAddr);
	char recvBuf[4096];

	u_long blockMode = 1;//将srvSock设为非阻塞模式以监听客户连接请求

	if ((rtn = ioctlsocket(srvSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO：允许或禁止套接口s的非阻塞模式。
		cout << "ioctlsocket() failed with error!\n";
		return;
	}
	cout << "ioctlsocket() for server socket ok!	Waiting for client connection and data\n";

	//清空read,write描述符，对rfds和wfds进行了初始化，必须用FD_ZERO先清空，下面才能FD_SET
	FD_ZERO(&rfds);
	FD_ZERO(&wfds);

	//设置等待客户连接请求
	FD_SET(srvSocket, &rfds);

	while(true){
		//清空read,write描述符
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);

		//设置等待客户连接请求
		FD_SET(srvSocket, &rfds);

		if (!first_connetion) {
			//设置等待会话SOKCET可接受数据或可发送数据
			FD_SET(sessionSocket, &rfds);
			FD_SET(sessionSocket, &wfds);
		}
		
		//开始等待
		int nTotal = select(0, &rfds, &wfds, NULL, NULL);

		//如果srvSock收到连接请求，接受客户连接请求
		if (FD_ISSET(srvSocket, &rfds)) {
			nTotal--;

			//产生会话SOCKET
			sessionSocket = accept(srvSocket, (LPSOCKADDR)&clientAddr, &addrLen);
			if (sessionSocket != INVALID_SOCKET)
				printf("Socket listen one client request!\n");

			//把会话SOCKET设为非阻塞模式
			if ((rtn = ioctlsocket(sessionSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO：允许或禁止套接口s的非阻塞模式。
				cout << "ioctlsocket() failed with error!\n";
				return;
			}
			cout << "client ip: " << inet_ntoa(clientAddr.sin_addr) << endl << "client port: " << htons(clientAddr.sin_port) << endl;
			cout << "ioctlsocket() for session socket ok!	Waiting for client connection and data\n";

			//设置等待会话SOKCET可接受数据或可发送数据
			FD_SET(sessionSocket, &rfds);
			FD_SET(sessionSocket, &wfds);

			first_connetion = false;

		}

		//检查会话SOCKET是否有数据到来
		if (nTotal > 0) {
			//如果会话SOCKET有数据到来，则接受客户的数据
			if (FD_ISSET(sessionSocket, &rfds)) {
				//receiving data from client
				memset(recvBuf, '\0', 4096);
				rtn = recv(sessionSocket, recvBuf, 256, 0);
				if (rtn > 0) {
					cout << "Received " << rtn << " bytes from client:" << endl  << recvBuf  << endl;
					//printf("Received %d bytes from client: %s\n", rtn, recvBuf);
				}
				else {
					printf("Client leaving ...\n");
					closesocket(sessionSocket);  //既然client离开了，就关闭sessionSocket
				}
				//文件
				string filepath = main_directory + recvBuf;
				cout << "path:" << filepath << endl;
				send_http()
			}
		}	
	}

}

void send_http(SOCKET s, string filepath)
{
	string file_extension = file_type_analysis(filepath);

	string content_type = "text/plain";
	string body_length = "Content-Length: ";
	unordered_map<string, string> type_map = { {"html", "text/html"},{"gif", "image/gif"},{"jpg", "image/jpg"}, {"png", "image/png"} };

	content_type = type_map[file_extension.c_str()];
	string ok_head = "HTTP/1.1 200 OK\r\n";
	string not_acc_head = "HTTP/1.1 406 Not Acceptable\r\n";
	string not_found_head = "HTTP/1.1 404 NOT FOUND\r\n";
	string temp_1 = "Content-type: ";
	if (content_type == "")
	{
		cout << "406 Not Acceptable!" << endl;
		send(s, not_acc_head.c_str(), not_acc_head.length(), 0);
		closesocket(s);
		*i--;
		return;
	}
	FILE* pfile = fopen(filepath.c_str(), "rb");
	if (pfile == NULL)
	{
		cout << "404 not found!" << endl;
		send(s, not_found_head.c_str(), not_found_head.length(), 0);
		closesocket(s);
		*i--;
		return;
	}
	else if (send(s, ok_head.c_str(), ok_head.length(), 0) == -1)
	{
		cout << "Sending error" << endl;
		closesocket(s);
		*i--;
		return;
	}
	if (content_type.c_str())
	{
		temp_1 += content_type;
		temp_1 += "\r\n";

		if (send(s, temp_1.c_str(), temp_1.length(), 0) == -1)
		{
			cout << "Sending error!" << endl;
			closesocket(s);
			*i--;
			return;
		}
	}
	send(s, "\r\n", 2, 0);

	fseek(pfile, 0L, SEEK_END);
	int flen = ftell(pfile);
	char* p = (char*)malloc(flen + 1);
	fseek(pfile, 0L, SEEK_SET);
	fread(p, flen, 1, pfile);
	send(s, p, flen, 0);

	cout << endl << "file " << filepath << " sent successfully! o(￣▽￣)ｄ" << endl;
	return;
}