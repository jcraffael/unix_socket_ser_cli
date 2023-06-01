#ifndef INT_SOCKET_SER_
#define INT_SOCKET_SER_

#include "int_socket.hpp"

//extern char destination[];
class int_socket_ser: public int_socket
{
    public:
    int_socket_ser() :
    int_socket(){
    };
    int_socket_ser(int_socket_ser& other) = delete;
    int_socket_ser(int_socket_ser&& other) = delete;
    RC binding(/*int sockfd, struct sockaddr_in addr*/);
    RC connect_to(/*int sockfd, struct sockaddr_in addr*/);
    RC listen_to_connection(/*int sockfd, int num*/);

};

#endif