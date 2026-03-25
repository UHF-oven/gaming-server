#!/bin/bash



rm ./*.a
rm ./*.o
rm ./app
rm ./client_app


g++ -c struct.cpp -o struct.o 
ar rcs libstruct.a struct.o


g++ -c client_tread.cpp -I. -o client_tread.o
ar rcs libclient_tread.a client_tread.o

g++ main.cpp -L . -lstruct -lclient_tread -o app





g++ -c custom_read.cpp -o custom_read.o
ar rcs libcustom_read.a custom_read.o


g++ client_app.cpp -L . -lstruct -lcustom_read -o client_app
