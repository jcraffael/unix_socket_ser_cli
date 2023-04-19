
#include "int_socket_cli.hpp"
#include "utils.hpp"
#include "mes_process.hpp"
#define debug 1

using namespace std;

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_ERROR, INFO, "Arguments missing!");
      exit(EXIT_FAILURE);
   }
      
   int sockfd, sent_recv_bytes = 0;
   struct sockaddr_in serv_addr;
   
   
   char buffer[BUF_SIZE];

   
   /* Create a socket point */
   int_socket_cli client = int_socket_cli();
   sockfd = client.get_sock();
   #ifdef debug
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Client socket created successfully with fd %d!", sockfd);
   #endif
   
   serv_addr = client.get_addr();
   client.connect_to(sockfd, serv_addr);

   #ifdef debug
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Client connected to server successfully!");
   #endif


   mes_buf *mbuf = ProcessArgs(argc, argv);
   // if(argc >= 4)
   //    mbuf = init_mes_buf(tuppercase(argv[1] + 2), argv[2], argv[3]);
   // else
   //    mbuf = init_mes_buf(tuppercase(argv[1] + 2), argv[2]);

   #ifdef debug
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Action is %s and key is %s", argv[1] + 2, argv[2]);
   #endif

   create_client_buffer(mbuf, buffer);
   

   /* Send message to the server */
   
   //cout << "Buffer:" << buffer << endl;
   sent_recv_bytes = write(sockfd, buffer, BUF_SIZE);
   
   if (sent_recv_bytes < 0) {
      perror("ERROR writing to socket");
      exit(EXIT_FAILURE);
   }
   #ifdef debug
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Sent %d bytes to the server ...", sent_recv_bytes);
   #endif

   /* Now read server response */
   memset(buffer, 0, BUF_SIZE);
   sent_recv_bytes = read(sockfd, buffer, BUF_SIZE);
   
   if (sent_recv_bytes < 0) {
      perror("ERROR reading from socket");
      exit(EXIT_FAILURE);
   }

   rep_buf *rbuf = (rep_buf *)buffer;

	#ifdef debug
      traceEvent(TRACE_LEVEL, TRACE_LEVEL_NORMAL, INFO, "Reply from server: %d %s", rbuf->res, rbuf->k_val);
   #endif

   delete mbuf;
   //cout << buffer << endl;
   return 0;
}