#pragma once
#include "winsock2.h"
#include <stdio.h>
#include <iostream>
using namespace std;

#pragma comment(lib,"ws2_32.lib")

void main(){

	//��ʼ��Winsock����
	freopen("./config.txt", "r", stdin);
	WSADATA wsaData;
	fd_set rfds;				//���ڼ��socket�Ƿ������ݵ����ĵ��ļ�������������socket������ģʽ�µȴ������¼�֪ͨ�������ݵ�����
	fd_set wfds;				//���ڼ��socket�Ƿ���Է��͵��ļ�������������socket������ģʽ�µȴ������¼�֪ͨ�����Է������ݣ�
	bool first_connetion = true;

	int nRc = WSAStartup(0x0202,&wsaData);

	if(nRc){
		cout<<"Winsock  startup failed with error!\n";
	}

	if(wsaData.wVersion != 0x0202){
		cout << "Winsock version is not correct!\n";
	}

	cout << "Winsock  startup Ok!\n";

	//���ü�����ַ�������˿ں���Ŀ¼ 
	

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

	u_long blockMode = 1;//��srvSock��Ϊ������ģʽ�Լ����ͻ���������

	if ((rtn = ioctlsocket(srvSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO��������ֹ�׽ӿ�s�ķ�����ģʽ��
		cout << "ioctlsocket() failed with error!\n";
		return;
	}
	cout << "ioctlsocket() for server socket ok!	Waiting for client connection and data\n";

	//���read,write����������rfds��wfds�����˳�ʼ����������FD_ZERO����գ��������FD_SET
	FD_ZERO(&rfds);
	FD_ZERO(&wfds);

	//���õȴ��ͻ���������
	FD_SET(srvSocket, &rfds);

	while(true){
		//���read,write������
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);

		//���õȴ��ͻ���������
		FD_SET(srvSocket, &rfds);

		if (!first_connetion) {
			//���õȴ��ỰSOKCET�ɽ������ݻ�ɷ�������
			FD_SET(sessionSocket, &rfds);
			FD_SET(sessionSocket, &wfds);
		}
		
		//��ʼ�ȴ�
		int nTotal = select(0, &rfds, &wfds, NULL, NULL);

		//���srvSock�յ��������󣬽��ܿͻ���������
		if (FD_ISSET(srvSocket, &rfds)) {
			nTotal--;

			//�����ỰSOCKET
			sessionSocket = accept(srvSocket, (LPSOCKADDR)&clientAddr, &addrLen);
			if (sessionSocket != INVALID_SOCKET)
				printf("Socket listen one client request!\n");

			//�ѻỰSOCKET��Ϊ������ģʽ
			if ((rtn = ioctlsocket(sessionSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO��������ֹ�׽ӿ�s�ķ�����ģʽ��
				cout << "ioctlsocket() failed with error!\n";
				return;
			}
			cout << "client ip: " << inet_ntoa(clientAddr.sin_addr) << endl << "client port: " << htons(clientAddr.sin_port) << endl;
			cout << "ioctlsocket() for session socket ok!	Waiting for client connection and data\n";

			//���õȴ��ỰSOKCET�ɽ������ݻ�ɷ�������
			FD_SET(sessionSocket, &rfds);
			FD_SET(sessionSocket, &wfds);

			first_connetion = false;

		}

		//���ỰSOCKET�Ƿ������ݵ���
		if (nTotal > 0) {
			//����ỰSOCKET�����ݵ���������ܿͻ�������
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
					closesocket(sessionSocket);  //��Ȼclient�뿪�ˣ��͹ر�sessionSocket
				}
				//�ļ�
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

	cout << endl << "file " << filepath << " sent successfully! o(������)��" << endl;
	return;
}