#include "mes_process.hpp"


// mes_buf *init_mes_buf(char *act, char *cont, char *val)
// {
//     mes_buf *mbuf = new mes_buf();
//     memcpy(mbuf->act, act, BUF_ACT);
//     memcpy(mbuf->cont, cont, BUF_CONT);
//     if(val)
//         memcpy(mbuf->val, val, BUF_VAL);
//     return mbuf;
// }

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
    memcpy(buff, buf, sizeof(mes_buf));

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


mes_buf *ProcessArgs(int argc, char** argv)
{

    mes_buf *mbuf = new mes_buf();
    if(argc == 1)
    {
        perror("Missing argument!");
        exit(EXIT_FAILURE);
    }
    auto construct_mbuf = [](mes_buf *buf, const char *str, char *arg)
    {
        memcpy(buf->act, str, BUF_ACT);
        memcpy(buf->cont, arg, BUF_CONT);
    };
    
    int opt;
    while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1)
    {
        
        switch (opt)
        {
        case 'l':
            construct_mbuf(mbuf, "LOAD", optarg);
            break;

        case 'g':
            construct_mbuf(mbuf, "GET", optarg);
            break;

        case 's':
            construct_mbuf(mbuf, "SET", optarg);
            if(argc > 3)
                memcpy(mbuf->val, argv[3], BUF_VAL);
            break;
        case 'h': // -h or --help
        case '?': // Unrecognized option
        default:
            PrintHelp();
            break;
        }
    }

    return mbuf;
}