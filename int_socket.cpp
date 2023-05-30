#include "int_socket.hpp"

int_socket::int_socket(/*int domain, int type, int protocol, int port, char* ip_addr*/)
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    newfd = -1;
    if(sockfd < 0)
    {
        perror("Error opening socket ...");
        exit(RC_SOCKET_ERROR);
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

int int_socket::receive_data(char *buf, size_t buf_size)
{
    int fd_ = newfd == -1 ? sockfd : newfd;
    int sent_recv_bytes = read(fd_, buf, buf_size);
    // if (sent_recv_bytes < 0) {
    //     perror("ERROR reading from socket");
    //     return(RC_RECV_ERROR);
    // }
    return sent_recv_bytes;
}
int int_socket::send_data(char *buf, size_t buf_size)
{
    int fd_ = newfd == -1 ? sockfd : newfd;
    int sent_recv_bytes = write(fd_, buf, buf_size);
    // if (sent_recv_bytes < 0) {
    //     perror("ERROR reading from socket");
    //     return(RC_RECV_ERROR);
    // }
    return sent_recv_bytes;
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
