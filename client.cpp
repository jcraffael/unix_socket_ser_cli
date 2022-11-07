#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "lib_shared/lib_shared.h"

#define UDP_PORT 12345
#define BUF_SIZE 256
using namespace std;

int main(int argc, char *argv[])
{
    if(argc < 2) exit(0);
   int sockfd, sent_recv_bytes = 0;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   
   char buffer[BUF_SIZE];

   
   /* Create a socket point */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
	
   
   //bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
   
   serv_addr.sin_port = htons(UDP_PORT);
   
   /* Now connect to the server */
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      exit(1);
   }
   
   /* Now ask for a message from the user, this message
      * will be read by server
   */
   memset(buffer, 0, BUF_SIZE);

   string action(argv[1]);
   
   if(action == "--load")
   {
    if(argc != 3)
    {
        perror("Incorrect arguments!");
        exit(1);
    }
    sprintf(buffer, "LOAD %s\n", argv[2]);
   }
   else if(action == "--get")
   {
    if(argc != 3)
    {
        perror("Incorrect arguments!");
        exit(1);
    }
    sprintf(buffer, "GET %s\n", argv[2]);
   }
   else if(action == "--set")
   {
    if(argc != 4)
    {
        perror("Incorrect arguments!");
        exit(1);
    }
    char value[24];
    memset(value, 0, 24);
    memcpy(value, argv[3] + 1, strlen(argv[3] - 2));

    sprintf(buffer, "SET %s %s\n", argv[2], value);
   }

   /* Send message to the server */
   sent_recv_bytes = write(sockfd, buffer, BUF_SIZE);
   
   if (sent_recv_bytes < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
   
   /* Now read server response */
   memset(buffer, 0, BUF_SIZE);
   sent_recv_bytes = read(sockfd, buffer, 255);
   
   if (sent_recv_bytes < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
	
   printf("%s\n",buffer);
   return 0;
}