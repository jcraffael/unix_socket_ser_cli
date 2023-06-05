#include "int_socket_ser.hpp"

RC int_socket_ser::binding(/*int sockfd, struct sockaddr_in addr*/)
{
    
    if(bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
    {
        //perror("Error in binding ...");
        //exit(RC_SOCKET_ERROR);
        throw RC_SOCKET_ERROR;
    }
    return RC_SUCCESS;
}

RC int_socket_ser::listen_to_connection(/*int sockfd, int num*/)
{
    if(listen(sockfd, 5) < 0)
    {
        //perror("Error in listening ...");
        //exit(RC_SOCKET_ERROR);
        throw RC_SOCKET_ERROR;
    }
    return RC_SUCCESS;
}

RC int_socket_ser::connect_to(/*int sockfd, struct sockaddr_in addr*/)
{
    int len = sizeof(addr);
    newfd = accept(sockfd, (struct sockaddr *)&addr, (socklen_t *)&len);
    if(newfd < 0)
    {
        //perror("Error in accept ...");
        //exit(RC_SOCKET_ERROR);
        throw RC_ACCEPT_ERROR;
    }
    return RC_SUCCESS;
}
