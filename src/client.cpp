
#include "int_socket_cli.hpp"
#include "utils.hpp"
#include "mes_process.hpp"
//define debug 1

using namespace std;

int main(int argc, char *argv[])
{
   // if(argc < 3)
   // {
   //    traceEvent(TRACE_LEVEL, TRACE_LEVEL_ERROR, INFO, "Arguments missing!");
   //    exit(EXIT_FAILURE);
   // }
 
   int sent_recv_bytes = 0;
   char buffer[BUF_SIZE];

   /* Create a socket point */
   int_socket_cli client = int_socket_cli();
   //sockfd = client.get_sock();
   #ifdef debug
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Client socket created successfully!");
   #endif
   
   client.connect_to();

   #ifdef debug
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Client connected to server successfully!");
   #endif

   mes_process s_message = mes_process(argc, argv);
   #ifdef debug
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Action is %s and key is %s", argv[1] + 2, argv[2]);
   #endif

   s_message.create_client_buffer(buffer);
   
   /* Send message to the server */
   //cout << "Buffer:" << buffer << endl;
   sent_recv_bytes = client.send_data(buffer, BUF_SIZE);
   
   if (sent_recv_bytes < 0) {
      perror("ERROR writing to socket");
      exit(RC_SENT_ERROR);
   }
   #ifdef debug
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Sent %d bytes to the server ...", sent_recv_bytes);
   #endif

   /* Now read server response */
   memset(buffer, 0, BUF_SIZE);
   sent_recv_bytes = client.receive_data(buffer, BUF_SIZE);
   
   if (sent_recv_bytes < 0) {
      perror("ERROR reading from socket");
      exit(RC_RECV_ERROR);
   }

   rep_process r_message = rep_process(buffer);
	#ifdef debug
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Reply from server: %d %s", r_message.rec_code(), r_message.rec_val());
   #endif

   //cout << buffer << endl;
   return 0;
}