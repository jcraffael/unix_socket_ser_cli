
#include "libshared/libshared.hpp"
#include "int_socket_ser.hpp"
#include "utils.hpp"
#include "mes_process.hpp"
#include <sys/types.h>
#include <csignal>

//define debug 1
using namespace std;

void signal_handler(int)
{
    cout << "Received SIGINT, shutting down the server..." << endl;
    exit(RC_SUCCESS);
}

void init_int_socket()
{
    string action {};
    string content {};
    
   //int sockfd, newsockfd;
   char buffer[BUF_SIZE];
   
   int sent_recv_bytes;
   
   int_socket_ser server = int_socket_ser();
   //sockfd = server.get_sock();
    
    traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Server socket created successfully");
    server.binding();
    server.listen_to_connection();
    traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Server socket bond successfully and is listening ...");
    
   
   while(1)
   {
    
    signal(SIGINT, signal_handler);//(sighandler_t *)signal_handler);
    traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Server socket waiting for new connection ...");
    server.connect_to();
     
    traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Connection accepted, waiting for data from the client through new sock.");
    
    /* If connection is established then start communicating */
    memset(buffer, 0, BUF_SIZE);
    sent_recv_bytes = server.receive_data(buffer, BUF_SIZE);
    
    if (sent_recv_bytes < 0) {
        perror("ERROR reading from socket");
        continue;
    }
    
    traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Server recvd %d bytes from client: %s", sent_recv_bytes, buffer);
    mes_process m_process = mes_process(buffer);
    string action{m_process.get_act()};
    string key{m_process.get_cont()};
    string value{m_process.get_val()};
    short res{};
    string k_value{};
     
    traceEvent(TRACE_LEVEL, TRACE_LEVEL_DEBUG, INFO, "Action is: %s, content is: %s", m_process.get_act(), m_process.get_cont());
    switch(action.c_str()[0])
    {
        case 'L':
            res = load_resource(key);      
            traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Loading file in %s", key.c_str());

            break;
        case 'G':
            res = get_value(key, k_value);
            traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Geting value from key %s", key.c_str());
            break;
        case 'S':
            res = set_value(key, value);
         
            traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Setting value %s for key %s", value.c_str(), key.c_str());
            break;
        default:
            res = RC_GENERIC;        
            traceEvent(TRACE_LEVEL, TRACE_LEVEL_ERROR, INFO, "Incorrect action.");

    }
   
    //sprintf(buffer, "%u %s\n", res, k_value.length() ? k_value.c_str() : "");
    rep_process r_process = rep_process(res, k_value.c_str());

    r_process.create_server_buffer(buffer);    
    
    sent_recv_bytes = server.send_data(buffer, BUF_SIZE);

    traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Server sent %d bytes in reply to client: %s", sent_recv_bytes, buffer);

   }
   
}
int
main()
{

    init_int_socket();

    return 0;
}
