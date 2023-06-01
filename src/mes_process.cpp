#include "mes_process.hpp"

mes_process::mes_process(char *buff)
{
    new_message = new mes_buf();
    memcpy(new_message->act, buff, BUF_ACT);
    memcpy(new_message->cont, buff + BUF_ACT, BUF_CONT);
    memcpy(new_message->val, buff + BUF_ACT + BUF_CONT, BUF_VAL);

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

mes_process::mes_process(int argc, char** argv)
{
    new_message = new mes_buf();
    if(argc == 1)
    {
        //perror("Missing argument!");
        throw RC_MISS_ARGS;
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
        case 'v':
            TRACE_LEVEL = 3;
            break;
        case 'h': // -h or --help
        case '?': // Unrecognized option
        default:
            PrintHelp();
            throw RC_MISS_ARGS;
        }
    }
    //return mbuf;
}


rep_process::rep_process(short res, const char *k_val)
{
    new_rep = new rep_buf();
    new_rep->res = res;
    if(k_val)
        memcpy(new_rep->k_val, k_val, BUF_VAL);
}

rep_process::rep_process(char *buff)
{
    new_rep = new rep_buf();
    memcpy(new_rep, buff, sizeof(rep_buf));
}
void rep_process::create_server_buffer(char *buff)
{
    memset(buff, 0, BUF_SIZE);
    memcpy(buff, new_rep, sizeof(rep_buf));
}

rep_process::~rep_process()
{
    if(new_rep)
        delete new_rep;
}