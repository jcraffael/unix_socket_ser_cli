CC = g++
CFLAGS = -Wall -Wextra
TARGET = server libshared/libshared.so client
LIBS = -L ./libshared -lshared -lrt
OBJ = server.o client.o int_socket.o int_socket_ser.o
#DEPSRC = libshared/libshared.cpp
# default:
# 	 $(CC) $(CFLAGS) -g server.cpp $(DEPSRC) -o server -lrt
# 	 $(CC) $(CFLAGS) -g client.cpp $(DEPSRC) -o client -lrt

server: server.o int_socket_ser.o int_socket.o libshared/libshared.so
	$(CC) $(CFLAGS) server.o int_socket_ser.o int_socket.o -o server ${LIBS}

server.o: server.cpp int_socket_ser.hpp int_socket.hpp
	$(CC) $(CFLAGS) -c -I libshared server.cpp -o server.o

int_socket_ser.o: int_socket_ser.cpp 
	$(CC) $(CFLAGS) -c int_socket_ser.cpp -o int_socket_ser.o

int_socket.o: int_socket.cpp 
	$(CC) $(CFLAGS) -c int_socket.cpp -o int_socket.o

libshared/libshared.so:
	(cd libshared; make)

client: client.o
	$(CC) $(CFLAGS) client.o -o client

client.o: client.cpp
	$(CC) $(CFLAGS) -c client.cpp -o client.o

all:
	make
	(cd libshared; make)

clean:
	rm -f *.o
	(cd libshared; make clean)
