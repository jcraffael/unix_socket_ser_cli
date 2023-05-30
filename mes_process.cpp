#include "mes_process.hpp"

// rep_buf *init_rep_buf(short res, const char *k_val)
// {
//     rep_buf *rbuf = new rep_buf();
//     rbuf->res = res;
//     if(k_val)
//         memcpy(rbuf->k_val, k_val, BUF_VAL);
//     return rbuf;
    
// }

// void create_client_buffer(mes_buf *buf, char *buff)
// {
//     memset(buff, 0, BUF_SIZE);
//     memcpy(buff, buf, sizeof(mes_buf));

// }

// void create_server_buffer(rep_buf *buf, char *buff)
// {
//     memset(buff, 0, BUF_SIZE);
//     memcpy(buff, buf, sizeof(rep_buf));
// }

// mes_buf *parse_buffer(char *buff){

//     mes_buf *new_message = new mes_buf();
//     memcpy(new_message->act, buff, BUF_ACT);
//     memcpy(new_message->cont, buff + BUF_ACT, BUF_CONT);
//     memcpy(new_message->val, buff + BUF_ACT + BUF_CONT, BUF_VAL);
//     return new_message;
// }

mes_process::mes_process(char *buff)
{
    new_message = new mes_buf();
    memcpy(new_message->act, buff, BUF_ACT);
    memcpy(new_message->cont, buff + BUF_ACT, BUF_CONT);
    memcpy(new_message->val, buff + BUF_ACT + BUF_CONT, BUF_VAL);
    //return new_message;
}

mes_process::~mes_process()
{
    if(new_message)
        delete new_message;
}

void mes_process::create_client_buffer(char *buff)
{
    memset(buff, 0, BUF_SIZE);
    memcpy(buff, new_message, sizeof(mes_buf));

}

//mes_buf *ProcessArgs(int argc, char** argv)
mes_process::mes_process(int argc, char** argv)
{

    new_message = new mes_buf();
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
            construct_mbuf(new_message, "LOAD", optarg);
            break;

        case 'g':
            construct_mbuf(new_message, "GET", optarg);
            break;

        case 's':
            construct_mbuf(new_message, "SET", optarg);
            if(argc > 3)
                memcpy(new_message->val, argv[3], BUF_VAL);
            break;
        case 'h': // -h or --help
        case '?': // Unrecognized option
        default:
            PrintHelp();
            break;
        }
    }
    //return mbuf;
}


rep_process::rep_process(short res, const char *k_va)
{
    new_rep = new rep_buf();
    new_rep->res = res;
    if(k_val)
        memcpy(rbuf->k_val, k_val, BUF_VAL);
    //return rbuf;
}

rep_process::rep_process(char *buff)
{
    new_rep = (rep_buf *)buff;
}
void rep_process::create_server_buffer(char *buff)
{
    memset(buff, 0, BUF_SIZE);
    memcpy(buff, new_rep, sizeof(rep_buf));
}



rep_process::~rep_process()
{
    if(new_rep)
        delete(new_rep);
}