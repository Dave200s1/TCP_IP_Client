#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")


using namespace std;

int sendMessage(SOCKET clientSocket ){
    char message[] = "Hello, server!\n, I am David";
    if (send(clientSocket, message, sizeof(message), 0) < 0) {
        std::cerr << "Failed to send data" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
}

int checkConnection(SOCKET clientSocket, sockaddr_in serverAddress ){
        if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Failed to connect to server" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
}

int checkPackets(SOCKET clientSocket ){
    char buffer[1024];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead < 0) {
        std::cerr << "Failed to receive data" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
}

string showMessage(SOCKET clientSocket ){
    char buffer[1024];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Server response: " << buffer << std::endl;
}

int main (){
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Failed to create socket" << std::endl;
            WSACleanup();
            return 1;
        }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP
    serverAddress.sin_port = htons(8080); // Replace with server port


    checkConnection(clientSocket,serverAddress);

    sendMessage(clientSocket);

    checkPackets(clientSocket);


    showMessage(clientSocket);

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}