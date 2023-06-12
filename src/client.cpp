
#include "tcp_endpoint.hpp"
#include "utils.hpp"
#include "mes_process.hpp"

using namespace std;

int main(int argc, char *argv[])
{
   int sent_recv_bytes = 0;
   /* create message to send */
   mes_process *s_message;
   try
   {
      s_message = new mes_process(argc, argv);
   }
   catch(const RC &e)
   {
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_ERROR, INFO, log_msg[(int)e]/*"Missing arguments, exit..."*/);
      exit(RC_MISS_ARGS);
   }
    
   traceEvent(TRACE_LEVEL, TRACE_LEVEL_DEBUG, INFO, "Action is %s and key is %s", argv[1] + 2, argv[2]);
   /* Create a socket point */
   tcp_endpoint *client;
   try
   {
      client = new tcp_endpoint(0);// = int_socket_cli();
      //client->m_process = s_message;
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Client socket created successfully!");
      //client.connect_to();
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Client connected to server successfully!");
      
      client->set_buf((char *)(s_message->get_message()), BUF_SIZE);
      sent_recv_bytes = client->send_data();
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Sent %d bytes to the server ...", sent_recv_bytes);
      //memset(buffer, 0, BUF_SIZE);
      sent_recv_bytes = client->receive_data();
   }
   catch(const RC &e)
   {
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_ERROR, INFO, log_msg[(int)e]/*"Missing arguments, exit..."*/);
      exit(e);
   }

   rep_process r_message = rep_process(client->get_buf());
   traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Reply from server: %d %s", r_message.rec_code(), r_message.rec_val());

   delete s_message;
   delete client;
   return 0;
}