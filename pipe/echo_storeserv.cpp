#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 30
using namespace std;

void error_handling(char* message);
void read_childproc(int sig);


int main(int argc, char* argv[])
{
    int serv_sock, clnt_sock;
    sockaddr_in serv_adr,  clnt_adr;
    int fds[2];

    pid_t pid;
    struct sigaction act;
    socklen_t adr_sz;
    int str_len, state;
    char buf[BUF_SIZE];
    if(argc!=2)
    {
        cout << "Usage: " << argv[0] << "<IP> <port>" << endl;
        exit(1);
    }

    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    state = sigaction(SIGCHLD, &act, 0);

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        cout << error_handling("bind() error" );

    if(liste)



}
