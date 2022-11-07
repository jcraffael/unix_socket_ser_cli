CC = g++
CFLAGS = -Wall -Wextra
TARGET = server
//LIBS = -L ./lib_shared -lshard
DEPSRC = lib_shared/lib_shared.cpp
default:
	$(CC) $(CFLAGS) -g server.cpp $(DEPSRC) -o server -lrt
	$(CC) $(CFLAGS) -g client.cpp $(DEPSRC) -o client -lrt
# server.o: server.cpp
# 	$(CC) $(CFLAGS) -c server.cpp -o server.o

# server: server.o lib_shared/lib_shared.a
# 	$(CC) $(CFLAGS) server.o -o server ${LIBS}

# server: server.cpp lib_shared/lib_shared.a
#  	$(CC) $(CFLAGS) server.cpp lib_shared/lib_shared.a -o server

# lib_shared/lib_shared.a:
# 	(cd lib_shared; make)

# all:
# 	make
# 	(cd lib_shared; make)

clean:
	rm -f *.o

