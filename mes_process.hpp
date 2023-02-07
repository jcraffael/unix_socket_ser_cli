#ifndef MESS_H_
#define MESS_H_

#include <cstring>


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

mes_buf *init_mes_buf(char *act, char *cont, char *val = NULL);
rep_buf *init_rep_buf(short res, const char *k_val = NULL);
void create_client_buffer(mes_buf *buf, char *buff);
void create_server_buffer(rep_buf *buf, char *buff);
mes_buf *parse_buffer(char *buff);

#endif