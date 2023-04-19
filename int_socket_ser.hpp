#ifndef INT_SOCKET_SER_
#define INT_SOCKET_SER_

#include "int_socket.hpp"

//extern char destination[];
class int_socket_ser: public int_socket
{
    private:
    int newsockfd;

    public:
    int_socket_ser() :
    int_socket(){
        //set_connection(connect_to(get_sock(), get_addr()));
    };
    int binding(int sockfd, struct sockaddr_in addr);
    int connect_to(int sockfd, struct sockaddr_in addr);
    int listen_to_connection(int sockfd, int num);
    //int accept_new_connection(int sockfd, struct sockaddr_in addr);
    //void set_newfd();
    //int test_new_connection();
    int get_newfd();
    

};

#endif