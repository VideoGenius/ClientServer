
#include <iostream>
#include <winsock2.h> // Include Winsock header

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error initializing Winsock" << std::endl;
        return 1;
    }
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address
    serverAddress.sin_port = htons(8080); // Server port number

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error connecting to server" << std::endl;
        closesocket(clientSocket);
        return 1;
    }

    int num1, num2;
    std::cout << "Enter two numbers: ";
    std::cin >> num1 >> num2;

    send(clientSocket, &num1, sizeof(num1), 0);
    send(clientSocket, &num2, sizeof(num2), 0);

    int result;
    recv(clientSocket, &result, sizeof(result), 0);

    std::cout << "Result received from server: " << result << std::endl;

    closesocket(clientSocket);
    return 0;
}
