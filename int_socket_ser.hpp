#ifndef INT_SOCKET_SER_
#define INT_SOCKET_SER_

#include "int_socket.hpp"

class int_socket_ser: public int_socket
{
    private:
    int newsockfd;

    public:
    int_socket_ser(int domain, int type, int protocol, int port, char *ip_addr) :
    int_socket(domain, type, protocol, port, ip_addr){
        //set_connection(connect_to(get_sock(), get_addr()));
    };
    void binding(int sockfd, struct sockaddr_in addr);
    int connect_to(int sockfd, struct sockaddr_in addr);
    int listen_to_connection(int sockfd, int num);
    //int accept_new_connection(int sockfd, struct sockaddr_in addr);
    //void set_newfd();
    //int test_new_connection();
    int get_newfd();
    

};

#endif