
#include "int_socket_cli.hpp"
#include "utils.hpp"
#define debug 

using namespace std;

const vector<string>actions {"--load", "--get", "--set"};

char *tuppercase(char *str)
{
   for(int i = 0; i < strlen(str); i++)
      str[i] -= 32;
   return str;
}

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      traceEvent(TRACE_LEVEL_ERROR, INFO, "Arguments missing!");
      exit(EXIT_FAILURE);
   }
      
   int sockfd, sent_recv_bytes = 0;
   struct sockaddr_in serv_addr;
   
   
   char buffer[BUF_SIZE];

   
   /* Create a socket point */
   int_socket_cli client = int_socket_cli(AF_INET, SOCK_STREAM, 0, UDP_PORT, destination);
   sockfd = client.get_sock();
   #ifdef debug
      traceEvent(TRACE_LEVEL_NORMAL, INFO, "Client socket created successfully with fd %d!", sockfd);
   #endif
   
   serv_addr = client.get_addr();
   client.connect_to(sockfd, serv_addr);

   #ifdef debug
      traceEvent(TRACE_LEVEL_NORMAL, INFO, "Client connected to server successfully!");
   #endif

   memset(buffer, 0, BUF_SIZE);
   string action(argv[1]);
   

   if(count(actions.begin(), actions.end(), action)) 
   {
      //cout << argv[1] + 2 << endl;
      sprintf(buffer, "%s %s", tuppercase(argv[1] + 2), argv[2]);
      if(action == "--set")
      {
         if(argc < 4)
         {
            cout << "Incorrect arguments!" << endl;
            exit(EXIT_FAILURE);
         }
         else
         {
            strcat(buffer, " ");
            strcat(buffer, argv[3]);
         }
      }

      #ifdef debug
         traceEvent(TRACE_LEVEL_NORMAL, INFO, "Action is %s and key is %s", argv[1] + 2, argv[2]);
      #endif
   }
   else
   {
      traceEvent(TRACE_LEVEL_ERROR, INFO, "Incorrect action!");
      exit(EXIT_FAILURE);
   }

   // if(action == "--load")
   // {
   //    sprintf(buffer, "LOAD %s\n", argv[2]);
   // }
   // else if(action == "--get")
   // {
   //    sprintf(buffer, "GET %s\n", argv[2]);
   // }
   // else if(action == "--set")
   // {
   //    if(argc < 4)
   //    {
   //       cout << "Incorrect arguments!" << endl;
   //       exit(EXIT_FAILURE);
   //    }

   //    sprintf(buffer, "SET %s %s\n", argv[2], argv[3]);
   //    cout << "key is " << argv[2] << " and value is " << argv[3] << endl;
   //    cout << "buffer is " << buffer << endl;
   // }
   // else
   // {
   //    cout << "Incorrect action!" << endl;
   //    exit(EXIT_FAILURE);
   // }


   /* Send message to the server */
   
   //cout << "Sending request to the server ..." << endl;
   sent_recv_bytes = write(sockfd, buffer, BUF_SIZE);
   
   if (sent_recv_bytes < 0) {
      perror("ERROR writing to socket");
      exit(EXIT_FAILURE);
   }
   #ifdef debug
      traceEvent(TRACE_LEVEL_NORMAL, INFO, "Sent %d bytes to the server ...", sent_recv_bytes);
   #endif

   /* Now read server response */
   memset(buffer, 0, BUF_SIZE);
   sent_recv_bytes = read(sockfd, buffer, BUF_SIZE);
   
   if (sent_recv_bytes < 0) {
      perror("ERROR reading from socket");
      exit(EXIT_FAILURE);
   }
	#ifdef debug
      traceEvent(TRACE_LEVEL_NORMAL, INFO, "Reply from server: %sReceived %d bytes from the server ...", buffer, sent_recv_bytes);
   #endif

   //cout << buffer << endl;
   return 0;
}