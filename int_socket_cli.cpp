#include "int_socket_cli.hpp"


int int_socket_cli::connect_to(int sockfd, struct sockaddr_in addr)
{
    int len = sizeof(addr);
    
    if(connect(sockfd, (struct sockaddr *)&addr, len))
    {
        perror("Error in connect ...");
        exit(4);
    }
    return 0;
}
