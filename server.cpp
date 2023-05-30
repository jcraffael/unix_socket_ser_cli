
#include "libshared/libshared.hpp"
#include "int_socket_ser.hpp"
#include "utils.hpp"
#include "mes_process.hpp"
#include <sys/types.h>
#include <csignal>
//define BUF_SIZE 256
#define debug 1
using namespace std;



void signal_handler(int)
{
    cout << "Received SIGINT, shutting down the server..." << endl;
    exit(EXIT_SUCCESS);

}


void init_int_socket()
{
    string action {};
    string content {};
    
   //int sockfd, newsockfd;
   char buffer[BUF_SIZE];
   //struct sockaddr_in serv_addr; 
   int sent_recv_bytes;
   
   int_socket_ser server = int_socket_ser();
   //sockfd = server.get_sock();
   #ifdef debug
        traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Server socket created successfully with fd %d.", sockfd);
    #endif
   
    
    //serv_addr = server.get_addr();
    server.binding(/*sockfd, serv_addr*/);
    server.listen_to_connection(/*sockfd, 5*/);
   #ifdef debug
        traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Server socket bond successfully and is listening ...");
    #endif
   
   while(1)
   {
    
    signal(SIGINT, signal_handler);//(sighandler_t *)signal_handler);
    #ifdef debug
        traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Server socket waiting for new connection ...");
    #endif

    server.connect_to(/*sockfd, serv_addr*/);
    //newsockfd = server.get_newfd();
    #ifdef debug
        traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Connection accepted, waiting for data from the client through new sock %d.", newsockfd);
    #endif
    
    /* If connection is established then start communicating */
    memset(buffer, 0, BUF_SIZE);
    sent_recv_bytes = server.receive_data(buffer, BUF_SIZE);
    
    if (sent_recv_bytes < 0) {
        perror("ERROR reading from socket");
        continue;
    }
    
    #ifdef debug
        traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Server recvd %d bytes from client: %s", sent_recv_bytes, buffer);
    #endif

    
    //mes_buf *mbuf = parse_buffer(buffer);
    mes_process m_process = mes_process(buffer);
    string action{m_process.get_act()};
    string key{m_process.get_cont()};
    string value{m_process.get_val()};
    short res{};
    string k_value{};
    #ifdef debug
        //traceEvent(TRACE_LEVEL, TRACE_LEVEL_DEBUG, INFO, "Action is: %s, content is: %s", mbuf->act, mbuf->cont);
    #endif

    switch(action.c_str()[0])
    {
        case 'L':
            res = load_resource(key);
        #ifdef debug
            traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Loading file in %s", key.c_str());
        #endif
            break;
        case 'G':
            res = get_value(key, k_value);
        #ifdef debug
            traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Geting value from key %s", key.c_str());
        #endif
            break;
        case 'S':
            res = set_value(key, value);
        #ifdef debug
            traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Setting value %s for key %s", value.c_str(), key.c_str());
        #endif
            break;
        default:
            res = 127;
        #ifdef debug
            traceEvent(TRACE_LEVEL, TRACE_LEVEL_ERROR, INFO, "Incorrect action.");
        #endif
    }
   
    //sprintf(buffer, "%u %s\n", res, k_value.length() ? k_value.c_str() : "");
    rep_process r_process = rep_process(res, k_value.c_str())
    //rep_buf *rbuf = init_rep_buf(res, k_value.c_str());
    
    r_process.create_server_buffer(buffer);    
    
    sent_recv_bytes = server.send_data(buffer, BUF_SIZE);
    //printf("Server sent %d bytes in reply to client: %s\n", sent_recv_bytes, buffer);
    #ifdef debug
        traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Server sent %d bytes in reply to client: %s", sent_recv_bytes, buffer);
    #endif

    //delete mbuf;
    //delete rbuf;

   }
   
}
int
main()
{

    init_int_socket();

    exit(EXIT_SUCCESS);
}
