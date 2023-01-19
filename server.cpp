#include <sys/types.h>
#include <csignal>
#include "libshared/libshared.hpp"
#include "int_socket_ser.hpp"

using namespace std;

void signal_handler(int)
{
    cout << "Received SIGINT, shutting down the server..." << endl;
    exit(EXIT_SUCCESS);

}

void init_int_socket()
{
    string action {};
    string content {};
    string path {};
   int sockfd, newsockfd;
   char buffer[BUF_SIZE];
   struct sockaddr_in serv_addr; 
   int sent_recv_bytes;
   
   int_socket_ser server = int_socket_ser(AF_INET, SOCK_STREAM, 0, UDP_PORT, DESTINATION);
   //server.test_socket();
   
    sockfd = server.get_sock();
    serv_addr = server.get_addr();
    server.binding(sockfd, serv_addr);

   server.listen_to_connection(sockfd, 5);
   
   while(1)
   {
    
    signal(SIGINT, signal_handler);//(sighandler_t *)signal_handler);
    cout << "Waiting for connection from client...\n";
    /* Accept actual connection from the client */
    //newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&clilen);
    server.connect_to(sockfd, serv_addr);
    newsockfd = server.get_newfd();

    cout << "Connection accepted, waiting for data from the client\n";
    /* If connection is established then start communicating */
    memset(buffer, 0, BUF_SIZE);
    sent_recv_bytes = read(newsockfd, buffer, BUF_SIZE);
    
    if (sent_recv_bytes < 0) {
        perror("ERROR reading from socket");
        continue;
    }
    
    printf("Server recvd %d bytes from client: %s\n", sent_recv_bytes, buffer);

    string buf_string(buffer);
    string k_value;
    int delim = buf_string.find(" ");
    action = buf_string.substr(0, delim);
    content = buf_string.substr(delim + 1, buf_string.length() - delim -2);
    uint16_t res;
    cout << "action is " << action << " and content is " << content << endl;
    if(action == "LOAD")
    {
        path = content;
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
        res = 127;

    memset(buffer, 0, BUF_SIZE);
    sprintf(buffer, "%u %s\n", res, k_value.length() ? k_value.c_str() : "");

    cout << "sending final result back to client\n";
    sent_recv_bytes = write(newsockfd, buffer, BUF_SIZE);
    printf("Server sent %d bytes in reply to client\n", sent_recv_bytes);

   }
   
}
int
main(int argc, char *argv[])
{

    init_int_socket();

    exit(EXIT_SUCCESS);
}
