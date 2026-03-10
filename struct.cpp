#include <iostream>
#include <string>
#include <stdexcept>

#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>


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



int main(){}
