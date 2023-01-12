#include <sys/types.h>
#include <csignal>
#include "libshared/libshared.hpp"
#include "int_socket_ser.hpp"

#define UDP_PORT 12345
#define BUF_SIZE 256
#define DESTINATION "127.0.0.1"
using namespace std;

void signal_handler(int)
{
    cout << "Received SIGINT, shutting down the server..." << endl;
    exit(EXIT_SUCCESS);

}

// void
// init_udp_socket(){
//     string action;
//     string content;
//     string k_value;
//     char buffer[BUF_SIZE];
//     int addr_size = 0, sent_recv_bytes = 0;
//     int udp_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    
//     if(udp_sock_fd == -1){
//         perror("Socket creation error");
//         exit(EXIT_FAILURE); 
//     }

//     struct sockaddr_in serv_addr, client_addr;
//     addr_size = sizeof(struct sockaddr);
//     serv_addr.sin_family      = AF_INET;
//     serv_addr.sin_port        = htons(UDP_PORT);
//     serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//     if (bind(udp_sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1) {
//         perror("Error : socket bind failed\n");
//         exit(EXIT_FAILURE); 
//     }

//     while(1)
//     {
//         memset(buffer, 0, BUF_SIZE);
//         printf("Waiting for data from the client\n");
//         sent_recv_bytes = recvfrom(udp_sock_fd, buffer, BUF_SIZE, 0, (struct sockaddr*)&client_addr, (socklen_t *)&addr_size);

//         if (sent_recv_bytes == -1) {
//             perror("Receive error");
//             exit(EXIT_FAILURE);
//         }
//         printf("Server recvd %d bytes from client\n", sent_recv_bytes);

//         string buf_string(buffer);
//         action = buf_string.substr(0, 3);
//         content = buf_string.substr(4, buf_string.length() - 5);
//         uint16_t res;
//         cout << "action is " << action << " and content is " << content << endl;
//         if(action == "LOAD")
//             res = load_resource(content);
//         else if(action == "GET")
//         {
//             string key = content;
//             //string value;
//             res = get_value(key, k_value);

//         }
//         else if(action == "SET")
//         {
//             string key = content.substr(0, key.find(" "));
//             string value = content.erase(0, key.find(" "));
//             res = set_value(key, value);
//         }

//         memset(buffer, 0, BUF_SIZE);
//         sprintf(buffer, "%d %s\n", res, k_value.c_str());

//         printf("sending final result back to client\n");
//         sent_recv_bytes = sendto(udp_sock_fd, buffer, BUF_SIZE, 0,
//                     (struct sockaddr *)&client_addr, addr_size);

//         printf("Server sent %d bytes in reply to client\n", sent_recv_bytes);
//     }

//     close(udp_sock_fd);
//     //remove_from_monitored_fd_set(connection_socket);
//     printf("connection closed..\n");

// }

void init_int_socket()
{
    string action;
    string content;
    
   int sockfd, newsockfd;
   char buffer[BUF_SIZE];
   struct sockaddr_in serv_addr; //, cli_addr;
   int sent_recv_bytes;
   
   int_socket_ser server = int_socket_ser(AF_INET, SOCK_STREAM, 0, UDP_PORT, DESTINATION);
   //server.test_socket();
    sockfd = server.get_sock();
    serv_addr = server.get_addr();
   server.connect_to(sockfd, serv_addr);
   server.test_new_connection();
   server.listen_to_connection(sockfd, 5);

   /* First call to socket() function */
//    sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
//    if (sockfd < 0) {
//       perror("ERROR opening socket");
//       exit(1);
//    }
   
//    /* Initialize socket structure */
//    memset((char *) &serv_addr, 0, sizeof(serv_addr));
   
   
//    serv_addr.sin_family = AF_INET;
//    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");;
//    serv_addr.sin_port = htons(UDP_PORT);
//     /* Now bind the host address using bind() call.*/
//    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
//       perror("ERROR on binding");
//       exit(1);
//    }
      
//    /* Now start listening for the clients, here process will
//       * go in sleep mode and will wait for the incoming connection
//    */
   
//    listen(sockfd,5);
//    clilen = sizeof(cli_addr);
   
   while(1)
   {
    signal(SIGINT, signal_handler);//(sighandler_t *)signal_handler);
    printf("Waiting for connection from client...\n");
    /* Accept actual connection from the client */
    //newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&clilen);
    newsockfd = server.get_newfd();
    server.test_new_connection();

    // if (newsockfd < 0) {
    //     perror("ERROR on accept");
    //     exit(1);
    // }
    printf("Connection accepted, waiting for data from the client\n");
    /* If connection is established then start communicating */
    memset(buffer, 0, BUF_SIZE);
    sent_recv_bytes = read(newsockfd, buffer, BUF_SIZE);
    
    if (sent_recv_bytes < 0) {
        perror("ERROR reading from socket");
        continue;
    }
    
    printf("Server recvd %d bytes from client\n", sent_recv_bytes);

    string buf_string(buffer);
    string k_value;
    int delim = buf_string.find(" ");
    action = buf_string.substr(0, delim);
    content = buf_string.substr(delim + 1, buf_string.length() - delim -2);
    uint16_t res;
    //cout << "action is " << action << " and content is " << content << endl;
    if(action == "LOAD")
    {
        string path = content;
        res = load_resource(path);
    }
    else if(action == "GET")
    {
        string key = content;
        //string value;
        res = get_value(key, k_value);

    }
    else if(action == "SET")
    {
        string key = content.substr(0, content.find(" "));
        string value = content.erase(0, content.find(" ") + 1);
        //cout << "key is " << key << " and value is " << value << endl;
        res = set_value(key, value);
    }
    else
        continue;

    memset(buffer, 0, BUF_SIZE);
    sprintf(buffer, "%u %s\n", res, k_value.length() ? k_value.c_str() : "");

    printf("sending final result back to client\n");
    sent_recv_bytes = write(newsockfd, buffer, BUF_SIZE);
    printf("Server sent %d bytes in reply to client\n", sent_recv_bytes);

   }
   //close(sockfd);
   
}
int
main(int argc, char *argv[])
{

    init_int_socket();

    exit(EXIT_SUCCESS);
}
