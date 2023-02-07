#include "mes_process.hpp"
//include "utils.hpp"

mes_buf *init_mes_buf(char *act, char *cont, char *val)
{
    mes_buf *mbuf = new mes_buf();
    memcpy(mbuf->act, act, BUF_ACT);
    memcpy(mbuf->cont, cont, BUF_CONT);
    if(val)
        memcpy(mbuf->val, val, BUF_VAL);
    return mbuf;
}

rep_buf *init_rep_buf(short res, const char *k_val)
{
    rep_buf *rbuf = new rep_buf();
    rbuf->res = res;
    if(k_val)
        memcpy(rbuf->k_val, k_val, BUF_VAL);
    return rbuf;
    
}

void create_client_buffer(mes_buf *buf, char *buff)
{
    memset(buff, 0, BUF_SIZE);
    size_t s = sizeof(mes_buf);
    memcpy(buff, buf, s);

}

void create_server_buffer(rep_buf *buf, char *buff)
{
    memset(buff, 0, BUF_SIZE);
    memcpy(buff, buf, sizeof(rep_buf));
}

mes_buf *parse_buffer(char *buff){

    mes_buf *new_message = new mes_buf();
    memcpy(new_message->act, buff, BUF_ACT);
    memcpy(new_message->cont, buff + BUF_ACT, BUF_CONT);
    memcpy(new_message->val, buff + BUF_ACT + BUF_CONT, BUF_VAL);
    return new_message;
}