
//include "libshared/libshared.hpp"
#include "int_socket_cli.hpp"


using namespace std;

int main(int argc, char *argv[])
{
   if(argc < 2) exit(0);
   int sockfd, sent_recv_bytes = 0;
   struct sockaddr_in serv_addr;
   
   
   char buffer[BUF_SIZE];

   
   /* Create a socket point */
   int_socket_cli client = int_socket_cli(AF_INET, SOCK_STREAM, 0, UDP_PORT, DESTINATION);
   sockfd = client.get_sock();
   serv_addr = client.get_addr();
   client.connect_to(sockfd, serv_addr);
   
   memset(buffer, 0, BUF_SIZE);

   string action(argv[1]);
   
   if(action == "--load")
   {
    if(argc != 3)
    {
        cout << "Incorrect arguments!" << endl;
        exit(EXIT_FAILURE);
    }
    sprintf(buffer, "LOAD %s\n", argv[2]);
   }
   else if(action == "--get")
   {
    if(argc != 3)
    {
        cout << "Incorrect arguments!" << endl;
        exit(EXIT_FAILURE);
    }
    sprintf(buffer, "GET %s\n", argv[2]);
   }
   else if(action == "--set")
   {
    if(argc != 4)
    {
        cout << "Incorrect arguments!" << endl;
        exit(EXIT_FAILURE);
    }
    char value[24];
    memset(value, 0, 24);
    memcpy(value, argv[3], strlen(argv[3]));

    sprintf(buffer, "SET %s %s\n", argv[2], value);
    cout << "key is " << argv[2] << " and value is " << argv[3] << endl;
    cout << "buffer is " << buffer << endl;
   }
   else
   {
      ;
   }

   /* Send message to the server */
   cout << "Sending request to the server ..." << endl;
   sent_recv_bytes = write(sockfd, buffer, BUF_SIZE);
   
   if (sent_recv_bytes < 0) {
      perror("ERROR writing to socket");
      exit(EXIT_FAILURE);
   }
   
   /* Now read server response */
   memset(buffer, 0, BUF_SIZE);
   sent_recv_bytes = read(sockfd, buffer, BUF_SIZE);
   
   if (sent_recv_bytes < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
	
   cout << buffer << endl;
   return 0;
}