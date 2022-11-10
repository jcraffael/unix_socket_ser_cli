CC = g++
CPPFLAGS = -fPIC -pedantic -Wall -Wextra
LDFLAGS = -shared
#LIB = lib_shared.a
TARGETS = lib_shared.so
OBJ = lib_shared.o 

lib_shared.so: lib_shared.o
	$(CC) $(LDFLAGS) -o lib_shared.so lib_shared.o

lib_shared.o: lib_shared.cpp 
	$(CC) $(CPPFLAGS) -c lib_shared.cpp -o lib_shared.o 

# ${LIB}: ${OBJ}
# 	ar rs ${LIB} ${OBJ}
# 	ranlib ${LIB}


clean:
	rm -f *.o
	rm -f ${TARGETS}

