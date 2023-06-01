#ifndef MESS_H_
#define MESS_H_

#include "utils.hpp"
#include <cstring>


#include <stdio.h>
#include <stdlib.h>

using namespace std;
#define BUF_ACT 5
#define BUF_CONT 80
#define BUF_VAL 40
#define BUF_SIZE BUF_ACT + BUF_CONT + BUF_VAL

class mes_process
{
private:
typedef struct mes_buf
{
    char act[BUF_ACT];
    char cont[BUF_CONT];
    char val[BUF_VAL];
    
}mes_buf;
mes_buf *new_message;
public:
    mes_process(char *buff);
    mes_process(int argc, char** argv);
    void create_client_buffer(char *buff);
    inline char* get_act() const { return new_message->act;}
    inline char* get_cont() const { return new_message->cont;}
    inline char* get_val() const { return new_message->val;}
    ~mes_process();
};

class rep_process
{
private:
    typedef struct rep_buf
    {
        short res;
        char k_val[BUF_VAL];
    }rep_buf;
    rep_buf *new_rep;
public:
    rep_process(short res, const char *k_val);
    rep_process(char *buff);
    void create_server_buffer(char *buff);
    inline short rec_code() const {return new_rep->res;}
    inline char* rec_val() const {return new_rep->k_val;}
    
    ~rep_process();
};


#endif