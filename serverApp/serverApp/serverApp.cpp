#include <iostream>
#include <winsock2.h> // Include Winsock header

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error initializing Winsock" << std::endl;
        return 1;
    }
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080); // Port number

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error binding socket" << std::endl;
        closesocket(serverSocket);
        return 1;
    }

    listen(serverSocket, 1);

    std::cout << "Server listening on port 8080..." << std::endl;

    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == -1) {
            std::cerr << "Error accepting client connection" << std::endl;
            continue;
        }

        int num1, num2;
        recv(clientSocket, (char*) & num1, sizeof(num1), 0);
        recv(clientSocket, (char*) & num2, sizeof(num2), 0);

        int result = num1 + num2;
        send(clientSocket,(char*) & result, sizeof(result), 0);

        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    return 0;
}
