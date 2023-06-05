
#include "int_socket_cli.hpp"
#include "utils.hpp"
#include "mes_process.hpp"
//define debug 1

using namespace std;

int main(int argc, char *argv[])
{
   int sent_recv_bytes = 0;
   char buffer[BUF_SIZE];

   /* create message to send */
   try
   {
      mes_process s_message = mes_process(argc, argv);
      s_message.create_client_buffer(buffer);
   }
   catch(const RC &e)
   {
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_ERROR, INFO, log_msg[(int)e]/*"Missing arguments, exit..."*/);
      exit(RC_MISS_ARGS);
   }
    
   traceEvent(TRACE_LEVEL, TRACE_LEVEL_DEBUG, INFO, "Action is %s and key is %s", argv[1] + 2, argv[2]);
   /* Create a socket point */
   try
   {
      int_socket_cli client;// = int_socket_cli();

      traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Client socket created successfully!");
      client.connect_to();
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Client connected to server successfully!");
      sent_recv_bytes = client.send_data(buffer, BUF_SIZE);
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Sent %d bytes to the server ...", sent_recv_bytes);
      memset(buffer, 0, BUF_SIZE);
      sent_recv_bytes = client.receive_data(buffer, BUF_SIZE);
   }
   catch(const RC &e)
   {
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_ERROR, INFO, log_msg[(int)e]/*"Missing arguments, exit..."*/);
      exit(e);
   }

   rep_process r_message = rep_process(buffer);
   traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Reply from server: %d %s", r_message.rec_code(), r_message.rec_val());

   return 0;
}