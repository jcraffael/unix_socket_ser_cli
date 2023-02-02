CC = g++
CFLAGS = -Wall -Wextra
TARGET = server client libshared/libshared.so 
LIBS = -L ./libshared -lshared -lrt
OBJ = server.o client.o utils.o int_socket.o int_socket_ser.o int_socket_cli.o 
BINS = server client
#DEPSRC = libshared/libshared.cpp
# default:
# 	 $(CC) $(CFLAGS) -g server.cpp $(DEPSRC) -o server -lrt
# 	 $(CC) $(CFLAGS) -g client.cpp $(DEPSRC) -o client -lrt

client: client.o int_socket_cli.o int_socket.o utils.o
	$(CC) $(CFLAGS) client.o int_socket_cli.o int_socket.o utils.o -o client

client.o: client.cpp int_socket_cli.hpp int_socket.hpp utils.hpp
	$(CC) $(CFLAGS) -c client.cpp -o client.o

server: server.o int_socket_ser.o int_socket.o utils.o libshared/libshared.so
	$(CC) $(CFLAGS) server.o int_socket_ser.o int_socket.o utils.o -o server ${LIBS}

server.o: server.cpp int_socket_ser.hpp int_socket.hpp utils.hpp
	$(CC) $(CFLAGS) -c -I libshared server.cpp -o server.o

int_socket_ser.o: int_socket_ser.cpp 
	$(CC) $(CFLAGS) -c int_socket_ser.cpp -o int_socket_ser.o

int_socket_cli.o: int_socket_cli.cpp 
	$(CC) $(CFLAGS) -c int_socket_cli.cpp -o int_socket_cli.o

int_socket.o: int_socket.cpp 
	$(CC) $(CFLAGS) -std=c++17 -c int_socket.cpp -o int_socket.o

utils.o: utils.cpp
	$(CC) $(CFLAGS) -c utils.cpp -o utils.o

libshared/libshared.so:
	(cd libshared; make)

all: $(BINS)
	make
	(cd libshared; make)


clean:
	rm -f *.o
	(cd libshared; make clean)
