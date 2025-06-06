#include "http_server.h"

std::string get_mime_type(const std::string &filepath) {
    size_t dotPos = filepath.find_last_of('.');
    if (dotPos == std::string::npos) return "application/octet-stream"; // 默认二进制类型

    std::string ext = filepath.substr(dotPos + 1);
    std::map <std::string, std::string> mime_types{
            {"html", "text/html"},
            {"css",  "text/css"},
            {"js",   "application/javascript"},
            {"jpg",  "image/jpg"},
            {"jpeg", "image/jpeg"},
            {"png",  "image/png"},
            {"gif",  "image/gif"},
            {"txt",  "text/plain"},
            {"ico",  "image/x-icon"},
            // 根据需要添加
    };

    if (mime_types.find(ext) != mime_types.end()) {
        return mime_types[ext];
    }
    return "application/octet-stream"; // 未知类型时返回默认
}

void send_http(const SOCKET &clientSock, const std::string &filepath) {
    std::ifstream file(filepath, std::ios::binary); // 使用二进制模式打开文件
    if (!file.is_open()) {
        // 如果文件未找到，返回 404 错误
        std::cout << "404 NOT FUND!" << std::endl;
        std::string errorResp = "HTTP/1.1 404 Not Found\r\n"
                           "Content-Type: text/html\r\n\r\n"
                           "<html>"
                           "<head><title>404 Not Found</title></head>"
                           "<body style='text-align:center; font-family:sans-serif;'>"
                           "<h1 style='color:red;'>404 Not Found</h1>"
                           "<p>Sorry, the page you are looking for does not exist.</p>"
                           "<a href='/' style='color:blue;'>Return to Home</a>"
                           "</body>"
                           "</html>";
        send(clientSock, errorResp.c_str(), static_cast<int>(errorResp.size()), 0);
        return;
    }

    // 获取文件内容
    std::cout << "200 OK" << std::endl;
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string mime_type = get_mime_type(filepath);
    std::string response = "HTTP/1.1 200 OK\r\n";
    response += "Server: VerySimpleServer\r\n";
    response += "Content-Type: " + mime_type + "\r\n";
    response += "Content-Length: " + std::to_string(fileSize) + "\r\n";
    response += "\r\n";  // 头部和正文的分隔

    send(clientSock, response.c_str(), static_cast<int>(response.size()), 0);

    // 发送文件内容
    char buffer[buf_size];
    while (file.read(buffer, sizeof(buffer))) {
        send(clientSock, buffer, static_cast<int>(file.gcount()), 0);
    }
    // 发送最后剩余的字节
    send(clientSock, buffer, static_cast<int>(file.gcount()), 0);

    file.close();
}

bool init_winsock(WSADATA &wsaData) {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        std::cout << "Winsock startup failed with error!\n";
        return false;
    }

    if (wsaData.wVersion != MAKEWORD(2, 2)) {
        std::cout << "Winsock version is not correct!\n";
        WSACleanup();
        return false;
    }
    std::cout << "Winsock startup Ok!\n";
    return true;
}

SOCKET create_srvSocket(const int &port, const std::string &ipaddr) {
    //create socket
    SOCKET srvSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (srvSocket == INVALID_SOCKET) {
        std::cout << "Socket creation failed!\n";
        WSACleanup();
        return INVALID_SOCKET;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.S_un.S_addr = inet_addr(ipaddr.c_str());

    std::cout << "Socket create Ok!\n";
    //bind
    if (bind(srvSocket, (LPSOCKADDR) &serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cout << "Socket bind Error!\n";
        return INVALID_SOCKET;
    }
    std::cout << "Socket bind Ok!\n";
    if (listen(srvSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cout << "Socket listen Error!\n";
        return INVALID_SOCKET;
    }
    std::cout << "Socket listen Ok!\n";
    //listen
    std::cout << "Waiting for client connection and data\n";
    return srvSocket;
}

void handle_client(SOCKET sessionSocket, sockaddr_in clientAddr, const std::string &main_directory) {
    char revBuff[buf_size]{};
    int rtn;
    while((rtn = recv(sessionSocket, revBuff, sizeof(revBuff), 0))>0){
        std::string request(revBuff);
        std::cout << "client ip: " << inet_ntoa(clientAddr.sin_addr) << std::endl
                  << "client port: " << htons(clientAddr.sin_port) << std::endl;
        size_t pos = request.find('\r'); // 找到第一行的结束符
        if (pos != std::string::npos) {
            std::string request_line = request.substr(0, pos); // 提取命令行
            std::cout << "Request Line: " << request_line << std::endl;
        }
        size_t space1 = request.find(' ');
        size_t space2 = request.find(' ', space1 + 1);
        std::string filepath = main_directory + request.substr(space1 + 1, space2 - space1 - 1);
        if (filepath == main_directory + "/")
            filepath += "index.html";
        send_http(sessionSocket, filepath);
    }
    if (rtn == 0) {
        std::cout << "Client disconnected." << std::endl;
    }
    closesocket(sessionSocket);
    std::cout << "Connection closed." << std::endl;
}

bool config(int &port ,std::string &ipaddr, std::string &main_directory)
{
    try {
        std::ifstream in("../config.ini");
        if (!in.is_open()) throw std::runtime_error("Could not open config.ini");
        in >> port >> ipaddr >> main_directory;
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return false;
    }

    return true;
}
