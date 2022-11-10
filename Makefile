CC = g++
CFLAGS = -Wall -Wextra
TARGET = server libshared/lib_shared.so client
LIBS = -L ./libshared -lshared -lrt
OBJ = server.o client.o
#DEPSRC = lib_shared/lib_shared.cpp
# default:
# 	 $(CC) $(CFLAGS) -g server.cpp $(DEPSRC) -o server -lrt
# 	 $(CC) $(CFLAGS) -g client.cpp $(DEPSRC) -o client -lrt

server: server.o libshared/lib_shared.so
	$(CC) $(CFLAGS) server.o -o server ${LIBS}

server.o: server.cpp
	$(CC) $(CFLAGS) -c -I libshared server.cpp -o server.o

# server: server.cpp lib_shared/lib_shared.a
#  	$(CC) $(CFLAGS) server.cpp lib_shared/lib_shared.a -o server

libshared/lib_shared.so:
	(cd libshared; make)

client: client.o
	$(CC) $(CFLAGS) client.o -o client

client.o: client.cpp
	$(CC) $(CFLAGS) -c client.cpp -o client.o

all:
	make
	(cd lib_shared; make)

clean:
	rm -f *.o
	(cd libshared; make clean)
