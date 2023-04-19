#ifndef MESS_H_
#define MESS_H_

#include <cstring>
#include <getopt.h>
//include <iostream>
#include <stdio.h>
//include <unistd.h>

using namespace std;
#define BUF_ACT 5
#define BUF_CONT 80
#define BUF_VAL 40
#define BUF_SIZE BUF_ACT + BUF_CONT + BUF_VAL

//const vector<string>actions {"--load", "--get", "--set"};

typedef struct mes_buf
{
    char act[BUF_ACT];
    char cont[BUF_CONT];
    char val[BUF_VAL];
    
}mes_buf;

typedef struct rep_buf
{
    short res;
    char k_val[BUF_VAL];
    
}rep_buf;

const char* const short_opts = "l:g:s:h";
const option long_opts[] = {
        {"load", required_argument, nullptr, 'l'},
        {"get", required_argument, nullptr, 'g'},
        {"set", required_argument, nullptr, 's'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, no_argument, nullptr, 0}
};

//mes_buf *init_mes_buf(char *act, char *cont, char *val = NULL);
rep_buf *init_rep_buf(short res, const char *k_val);
void create_client_buffer(mes_buf *buf, char *buff);
void create_server_buffer(rep_buf *buf, char *buff);
mes_buf *parse_buffer(char *buff);


// void inline PrintHelp()
// {
//     std::cout <<
//             "--num <n>:           Set number of program\n"
//             "--beep:              Beep the user\n"
//             "--sigma <val>:       Set sigma of program\n"
//             "--writeFile <fname>: File to write to\n"
//             "--help:              Show help\n";
//     exit(1);
// }


mes_buf *ProcessArgs(int argc, char** argv);


#endif