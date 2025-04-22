#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE 1024

void send_file(int client_sock, const char* file_name) {
    char buffer[SIZE];
    std::ifstream file(file_name, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "[-]Failed to open file.\n";
        close(client_sock);
        return;
    }

    while (!file.eof()) {
        file.read(buffer, SIZE);
        std::streamsize bytes_read = file.gcount();  // number of bytes actually read

        if (bytes_read > 0) {
            if (send(client_sock, buffer, bytes_read, 0) == -1) {
                std::cerr << "[-]Error sending file.\n";
                break;
            }
        }
    }

    std::cout << "[+]File sent to client.\n";
    file.close();
    close(client_sock);
    std::cout << "[+]Connection to client closed.\n\n";
}

int main(int argc, char* argv[]) {
    if(argc != 4)
    {
        printf("Usage: ./server <address> <port> <filename>\n");
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);
    const char* file_name = argv[3];

    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        std::cerr << "[-]Socket creation error\n";
        return 1;
    }
    std::cout << "[+]Server socket created.\n";

    // Set socket option SO_REUSEADDR
    int opt = 1;
    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "[-]setsockopt failed.\n";
        close(server_sock);
        return 1;
    }
    
    sockaddr_in server_addr{}, client_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    if (bind(server_sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "[-]Bind failed.\n";
        close(server_sock);
        return 1;
    }
    std::cout << "[+]Bind successful.\n";

    if (listen(server_sock, 10) != 0) {
        std::cerr << "[-]Listen failed.\n";
        close(server_sock);
        return 1;
    }
    std::cout << "[+]Server listening on port " << port << "...\n";

    while (true) {
        socklen_t addr_size = sizeof(client_addr);
        int client_sock = accept(server_sock, (sockaddr*)&client_addr, &addr_size);
        if (client_sock < 0) {
            std::cerr << "[-]Accept failed.\n";
            continue;
        }
        std::cout << "[+]Client connected.\n";

        std::thread t(send_file, client_sock, file_name);
        t.detach();  // Automatically reclaim resources when thread finishes
    }

    close(server_sock);
    return 0;
}
