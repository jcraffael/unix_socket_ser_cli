#include "int_socket_ser.hpp"

int int_socket_ser::connect_to(int sockfd, struct sockaddr_in addr)
{
    return bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
}

// int_socket_ser::int_socket_ser(int domain, int type, int protocol, int port, char *ip_addr) : int_socket(domain, type, protocol, port, ip_addr)
// {
    
//     set_connection(connect_to(get_sock(), get_addr()));
// }

int int_socket_ser::listen_to_connection(int sockfd, int num)
{
    if(listen(sockfd, num) < 0)
    {
        perror("Error in listening ...");
        exit(3);
    }
    return 0;
}

int int_socket_ser::accept_new_connection(int sockfd, struct sockaddr_in addr)
{
    int len = sizeof(addr);
    return accept(sockfd, (struct sockaddr *)&addr, (socklen_t *)&len);
}

void int_socket_ser::set_newfd()
{
    newsockfd = accept_new_connection(get_sock(), get_addr());
}

int int_socket_ser::test_new_connection()
{
    if(newsockfd < 0)
    {
        perror("Error in accept ...");
        exit(4);
    }
    return 0;
}

int int_socket_ser::get_newfd()
{
    return newsockfd;
}