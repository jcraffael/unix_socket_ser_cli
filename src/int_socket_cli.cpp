#include "int_socket_cli.hpp"


RC int_socket_cli::connect_to(/*int sockfd, struct sockaddr_in addr*/)
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
