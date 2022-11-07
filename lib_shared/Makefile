CC = g++
CFLAGS = -Wall -Wextra
LIB = lib_shared.a
OBJ = lib_shared.o 


lib_shared.o: lib_shared.cpp 
	$(CC) $(CFLAGS) -c lib_shared.cpp -o lib_shared.o 

${LIB}: ${OBJ}
	ar rs ${LIB} ${OBJ}
clean:
	rm -f *.o