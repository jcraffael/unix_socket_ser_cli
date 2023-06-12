#include "int_socket.hpp"
#include "mes_process.hpp"
#include <stdlib.h>
#include <vector>

#define MAX_SIZE 1024

class tcp_endpoint
{
private:
    int_socket *sock;
    char *buffer;
    int cli_fd;
    bool server_;
public:
    tcp_endpoint(bool server);
    ~tcp_endpoint();
    //rep_process *r_process;
    //mes_process *m_process;
    int receive_data();
    int send_data();
    void set_buf(char *buf, size_t size) { memset(buffer, 0, MAX_SIZE); 
    memcpy(buffer, buf, size);}
    char *get_buf() const {return buffer;}
    void new_connection();
};