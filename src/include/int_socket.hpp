#ifndef INT_SOCKET_
#define INT_SOCKET_

#include "utils.hpp"

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>


#define UDP_PORT 12345

inline char destination[] = "127.0.0.1";

class int_socket
{
    private:
    struct sockaddr_in addr;
    int sockfd;
    //int connection;

    public:
    int_socket();
    ~int_socket();
    RC binding(/*int sockfd, struct sockaddr_in addr*/);
    RC connect_to(/*int sockfd, struct sockaddr_in addr*/);
    //int accept_conn();
    RC listen_to_connection(/*int sockfd, int num*/);
    inline int get_fd(){return sockfd;}
    inline struct sockaddr_in *get_addr() {return &addr;}
    
};

#endif