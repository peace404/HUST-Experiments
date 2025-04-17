#include "http_server.h"


int main() {
    WSADATA wsaData;
    //初始化Winsock环境
    init_winsock(wsaData);
    int port;
    std::string ipaddr, main_directory;
    //配置监听地址、监听端口和主目录
    if (!config(port, ipaddr, main_directory))
        return 1;
    //create socket
    SOCKET srvSocket = create_srvSocket(port, ipaddr);
    if (srvSocket == INVALID_SOCKET) {
        return 1;
    }
    while (true) {
        sockaddr_in clientAddr{};
        int addrLen = sizeof(clientAddr);
        SOCKET sessionSocket = accept(srvSocket, (LPSOCKADDR) &clientAddr, &addrLen);
        if (INVALID_SOCKET == sessionSocket) {
            std::cout << "accept failed!\n" << std::endl;
            WSACleanup();
            system("pause");
            return -1;
        }
        std::cout << "Accepted a new client connection.\n";
        // 创建新线程处理客户端请求
        std::thread(handle_client, sessionSocket, clientAddr, main_directory).detach();
    }
}

