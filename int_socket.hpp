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
//define BUF_SIZE 256
inline char destination[] = "127.0.0.1";

class int_socket
{
    private:
    struct sockaddr_in addr;
    int sockfd;
    int connection;
    int newfd;

    public:
    int_socket();
    ~int_socket();
    virtual int connect_to(/*int sockfd, struct sockaddr_in addr*/) = 0;
    int receive_data(char *buf, size_t buf_size);
    int send_data(char *buf, size_t buf_size);
    // int get_sock();
    // int get_connection();
    // struct sockaddr_in get_addr();
    // void set_connection(int con);
};

#endif