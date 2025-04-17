#ifndef MULTI_THREAD_SERVER_HTTP_SERVER_H
#define MULTI_THREAD_SERVER_HTTP_SERVER_H

#include <string>
#include <winsock2.h>
#include <iostream>
#include <map>
#include <fstream>
#include <list>
#include <thread>
#include <atomic>
#include <csignal>

#define buf_size 4096
// 初始化Winsock
bool init_winsock(WSADATA &wsaData);

// 创建并绑定socket
SOCKET create_srvSocket(const int &port, const std::string &ipaddr);

// 处理客户端请求
void handle_client(SOCKET sessionSocket, sockaddr_in clientAddr, const std::string &main_directory);

// 获取MIME类型
std::string get_mime_type(const std::string &filepath);

// 发送HTTP响应
void send_http(const SOCKET &clientSock, const std::string &filepath);
bool config(int &port ,std::string &ipaddr, std::string &main_directory);

#endif
