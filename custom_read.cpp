#include "custom_read.hpp"



void custom_read(int fd, std::string& buffer, int buffer_size) {
    buffer.reserve(buffer_size);
    buffer.clear();
    char choise;
    ssize_t received;
    for (int i = 0; i < buffer_size; ++i) {
        received = recv(fd, &choise, 1, 0);
        if (choise == '\n' || received == EOF){
            break;
        }
        buffer += choise;
    }
    buffer += '\n';
}



