#ifndef INT_SOCKET_CLI_
#define INT_SOCKET_CLI_
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include "int_socket.hpp"

class int_socket_cli: public int_socket
{
    public:
    int_socket_cli(int domain, int type, int protocol, int port, char *ip_addr) :
    int_socket(domain, type, protocol, port, ip_addr){
        //set_connection(connect_to(get_sock(), get_addr()));
    };
    
    int connect_to(int sockfd, struct sockaddr_in addr);
    
    

};

#endif