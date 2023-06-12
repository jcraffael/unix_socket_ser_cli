#include "include/tcp_endpoint.hpp"

tcp_endpoint::tcp_endpoint(bool server)
{
    server_ = server;
    buffer = new char[MAX_SIZE];
    sock = new int_socket();
    if(server_)
    {
        sock->binding();
        sock->listen_to_connection();
    }
    else
        sock->connect_to();
}

tcp_endpoint::~tcp_endpoint()
{
    delete buffer;
    delete sock;
}
int tcp_endpoint::receive_data()
{
    memset(buffer, 0, MAX_SIZE);

    int fd_ = server_ ? cli_fd : sock->get_fd();
    int sent_recv_bytes = read(fd_, buffer, MAX_SIZE);
    if (sent_recv_bytes < 0) {
        throw RC_RECV_ERROR;
    }
    return sent_recv_bytes;

}
int tcp_endpoint::send_data()
{
    int fd_ = server_ ? cli_fd : sock->get_fd();
    int sent_recv_bytes = write(fd_, buffer, MAX_SIZE);
     if (sent_recv_bytes < 0) {
        throw RC_RECV_ERROR;
     }
    return sent_recv_bytes;
}

void tcp_endpoint::new_connection()
{
    int len = sizeof(*(sock->get_addr()));
    int newfd = accept(sock->get_fd(), (struct sockaddr *)(sock->get_addr()), (socklen_t *)&len);
    if(newfd < 0)
    {
        //perror("Error in accept ...");
        //exit(RC_SOCKET_ERROR);
        throw RC_ACCEPT_ERROR;
    }
    
    cli_fd = newfd;
}