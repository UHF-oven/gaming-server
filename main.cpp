#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

#define PORT 8080
#define BACKLOG 10



class Socket {
    int fd;
  public:
    Socket() { fd = socket(AF_INET, SOCK_STREAM, 0); if (fd < 0) throw std::runtime_error("Socket creation failed");}
    ~Socket() { if (fd >= 0) close(fd);}
    Socket(const Socket&) =delete;
    Socket& operator=(const Socket&) = delete;
    Socket(Socket&& other) noexcept : fd(other.fd){other.fd = -1;}
    int get() const {return fd;}
};





int main() {

    Socket main_socket;

    int enable = 1;
    setsockopt(main_socket.get(), SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
    
    
    struct sockaddr_in server_addr;



    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(main_socket.get(), (sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        perror("Error");
        exit(EXIT_FAILURE);
    }

    if (listen(main_socket.get(), BACKLOG) < 0){
        perror("listen() error");
        exit(EXIT_FAILURE);
    }


    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    std::cout << "Started\n";
    while(1){
        client_len = 0;
        client_fd = accept(main_socket.get(), (sockaddr*)&client_addr, &client_len);
        std:cout << "New client\n";
        if (client_fd < 1)
            continue;
        std::string buffer;
        buffer.resize(16384);
        read(client_fd, &buffer[0], 16384-1);

        write(client_fd, "hello", strlen("hello"));

        close(client_fd);

    
    }







}
