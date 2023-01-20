#ifndef INT_SOCKET_
#define INT_SOCKET_

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#define UDP_PORT 12345
#define BUF_SIZE 256

class int_socket
{
    private:
    struct sockaddr_in addr;
    int sockfd;
    int connection;

    public:
    int_socket(int domain, int type, int protocol, int port, char *ip_addr);
    ~int_socket();
    virtual int connect_to(int sockfd, struct sockaddr_in addr) = 0;
    int get_sock();
    int get_connection();
    struct sockaddr_in get_addr();
    void set_connection(int con);
    int test_connection();
    int test_socket();

};

#endif