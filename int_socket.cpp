#include "int_socket.hpp"

int_socket::int_socket(int domain, int type, int protocol, int port, char* ip_addr)
{
    sockfd = socket(domain, type, protocol);
    if(sockfd < 0)
    {
        perror("Error opening socket ...");
        exit(1);
    }
    
    addr.sin_family = domain;
    addr.sin_addr.s_addr = inet_addr(ip_addr);
    addr.sin_port = htons(port);
}
int_socket::~int_socket()
{
    if(sockfd > 0)
        close(sockfd);
}

int int_socket::get_sock()
{
    return sockfd;
}
struct sockaddr_in int_socket::get_addr()
{
    return addr;
}
int int_socket::get_connection()
{
    return connection;
}
void int_socket::set_connection(int con)
{
    connection = con;
}

// int int_socket::test_connection()
// {
//     if(connection < 0)
//     {
//         perror("Error in connection ...");
//         exit(2);
//     }
//     return 0;
// }
