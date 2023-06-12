#include "int_socket.hpp"

int_socket::int_socket(/*int domain, int type, int protocol, int port, char* ip_addr*/)
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //newfd = -1;
    if(sockfd < 0)
    {
        throw RC_SOCKET_ERROR;
    }
    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(destination);
    addr.sin_port = htons(UDP_PORT);
}
int_socket::~int_socket()
{
    if(sockfd > 0)
        close(sockfd);
}

RC int_socket::binding(/*int sockfd, struct sockaddr_in addr*/)
{
    
    if(bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
    {
        //perror("Error in binding ...");
        //exit(RC_SOCKET_ERROR);
        throw RC_SOCKET_ERROR;
    }
    return RC_SUCCESS;
}

RC int_socket::listen_to_connection(/*int sockfd, int num*/)
{
    if(listen(sockfd, 5) < 0)
    {
        //perror("Error in listening ...");
        //exit(RC_SOCKET_ERROR);
        throw RC_SOCKET_ERROR;
    }
    return RC_SUCCESS;
}

RC int_socket::connect_to()
{
    int len = sizeof(addr);
    if(connect(sockfd, (struct sockaddr *)&addr, len))
    {
        //perror("Error in connect ...");
        //exit(RC_CONNECTION_ERROR);
        throw RC_CONNECTION_ERROR;
    }
    return RC_SUCCESS;
}