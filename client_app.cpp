#include <iostream>
#include <array>
#include <string>

#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>



#include "struct.hpp"



int main(int argc, char **argv) {

    if (argc != 3){
        std::cout << "Usage: ./client_app [server IP] [server port] \n";
        exit(0);
    }

    std::string server_ip = argv[1];
    std::string server_port = argv[2];

    Socket my_socket;






    struct sockaddr_in server_addr;

    

    server_addr.sin_family = AF_INET;

    server_addr.sin_port = htons(std::stoi(server_port));


    if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0) {
        std::cout << "Wrong IP\n";
        exit(0);
    }
    
    if (connect(my_socket.get(), (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cout << "Connection failed\n";
        exit(1);
    }




    std::string input;
    std::array<char, 1024> buffer;
    read(my_socket.get(), buffer.data(), buffer.size());
    std::cout << buffer.data();
    int answer;

//    std::cout << "Now i'm waiting for connection\n";

    while(true) {
        read(my_socket.get(), buffer.data(), buffer.size());
        std::cout << buffer.data();
        while(true) {
            std::cin >> input;
            if (input != "rock" && input != "scissors" && input != "paper") {
                std::cout << "Wrong choise!\n";
            } else{
                break;
            }
        }

/*
        switch(input) {
            case "rock":
                answer = 1;
                break;
            case "scissors":
                answer = 2;
                break;
            case "paper":
                answer = 3;
                break;
        }
*/
        if (input == "rock") {
            answer = 1;
        } else if (input == "scissors") {
            answer = 2;
        } else if (input == "paper") {
            answer = 3;
        } else{
            std::cout << "Wrong argument! \n";
            exit(0);
        }

        answer += '0';
        send(my_socket.get(), &answer, 1, 0);
        std::cout << "i read and sent your choise\n";

        read(my_socket.get(), buffer.data(), buffer.size());
        std::cout << buffer.data();

    
    }






}
