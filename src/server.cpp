
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
    string key {};
    string value {};
    short res{};
    string k_value{};

   char buffer[BUF_SIZE];
   
   int sent_recv_bytes;
   
   int_socket_ser *server;
    try
    {
        server = new int_socket_ser();
        traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Server socket created successfully");
        server->binding();
        server->listen_to_connection();
        traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Server socket bond successfully and is listening ...");
    }
    catch(const RC &e)
   {
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_ERROR, INFO, log_msg[(int)e]/*"Missing arguments, exit..."*/);
      exit(e);
   }
   
   while(1)
   {
    signal(SIGINT, signal_handler);//(sighandler_t *)signal_handler);
    traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Server socket waiting for new connection ...");
    
    try
    {
        server->connect_to();
        traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Connection accepted, waiting for data from the client through new sock.");
        
        /* If connection is established then start communicating */
        memset(buffer, 0, BUF_SIZE);
        sent_recv_bytes = server->receive_data(buffer, BUF_SIZE);
    }
    catch(const RC &e)
    {
        traceEvent(TRACE_LEVEL, TRACE_LEVEL_ERROR, INFO, log_msg[(int)e]/*"Missing arguments, exit..."*/);
        continue;
    }
 
    traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Server recvd %d bytes from client: %s", sent_recv_bytes, buffer);
    mes_process m_process = mes_process(buffer);
    action = m_process.get_act();
    key = m_process.get_cont();
    value = m_process.get_val();
    k_value = "";
     
    traceEvent(TRACE_LEVEL, TRACE_LEVEL_DEBUG, INFO, "Action is: %s, content is: %s", m_process.get_act(), m_process.get_cont());
    switch(action.c_str()[0])
    {
        case 'L':
            if(res = load_resource(key))
                traceEvent(TRACE_LEVEL, TRACE_LEVEL_ERROR, INFO, "Resource file open error ...");
            else
                traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Loading file in %s", key.c_str());
            break;
        case 'G':
            res = get_value(key, k_value);
            if(res == 4)
                traceEvent(TRACE_LEVEL, TRACE_LEVEL_ERROR, INFO, "Resource file not loaded error ...");
            else if (res == 3)
                traceEvent(TRACE_LEVEL, TRACE_LEVEL_ERROR, INFO, "Missing key ...");
            else if (res == 255)
                traceEvent(TRACE_LEVEL, TRACE_LEVEL_ERROR, INFO, "No file available ...");
            else
                traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Geting value from key %s", key.c_str());
            break;
        case 'S':
            res = set_value(key, value);
            if(res == 4)
                traceEvent(TRACE_LEVEL, TRACE_LEVEL_ERROR, INFO, "Resource file not loaded error ...");
            else if (res == 255)
                traceEvent(TRACE_LEVEL, TRACE_LEVEL_ERROR, INFO, "No file available ...");
            else
                traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Setting value %s for key %s", value.c_str(), key.c_str());
            break;
        default:
            res = RC_GENERIC;        
            traceEvent(TRACE_LEVEL, TRACE_LEVEL_ERROR, INFO, "Incorrect action.");

    }
 
    rep_process r_process = rep_process(res, k_value.c_str());
    r_process.create_server_buffer(buffer);    

    try
    {
        sent_recv_bytes = server->send_data(buffer, BUF_SIZE);
        traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Server sent %d bytes in reply to client: %s", sent_recv_bytes, buffer);
    }
    catch(const RC &e)
    {
        traceEvent(TRACE_LEVEL, TRACE_LEVEL_ERROR, INFO, log_msg[(int)e]/*"Missing arguments, exit..."*/);
        continue;
    }
   }
   
   delete server;
}
int
main()
{

    init_int_socket();

    return 0;
}
