#!/bin/bash

g++ -c struct.cpp -o struct.o 
ar rcs libstruct.a struct.o


g++ -c client_tread.cpp -I. -o client_tread.o
ar rcs libclient_tread.a client_tread.o

g++ main.cpp -L . -lstruct -lclient_tread -o app




g++ client_app.cpp -L . -lstruct  -o client_app
