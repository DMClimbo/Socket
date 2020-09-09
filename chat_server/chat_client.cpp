#include<iostream>
#include<pthread.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>

using namespace std;
#define BUF_SIZE 100
#define NAME_SIZE 20

void* send_msg(void* arg);
void* recv_msg(void* arg);
void  error_handling(char* message);

char name[BUF_SIZE] = "[DEFALUT]";
char msg[BUF_SIZE];

int main(int argc, char* argv[])
{
    int sock;
    sockaddr_in serv_adr;
    pthread_t snd_thread, rcv_thread;
    void* thread_return;
    if(argc!=4)
    {
        cout << "Usage: " << argv[0] << "<IP> <port> <name>" << endl;
        exit(1);
    }

    sprintf(name, "[%s]", argv[3]);
    sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        error_handling("connect() error");

    pthread_create(&snd_thread, NULL, send_msg, (void*)&sock);
    pthread_create(&rcv_thread, NULL, recv_msg, (void*)&sock);
    pthread_join(snd_thread, &thread_return);
    pthread_join(rcv_thread, &thread_return);
    close(sock);
    return 0;
}




void* send_msg(void* arg)
{
    cout << "进入写线程" << endl;
    int sock = *((int*)arg);
    char name_msg[NAME_SIZE+BUF_SIZE];
    while(1)
    {
        fgets(msg, BUF_SIZE, stdin);
        if(!strcmp(msg, "q\n")||!strcmp(msg, "Q\n"))
        {
            close(sock);
            cout << "客户" << name << "已退出" << endl;
            exit(0);
        }
        sprintf(name_msg, "%s %s", name, msg);
        cout << name_msg << endl;
        if(write(sock, name_msg, strlen(name_msg))==-1)
            error_handling("write() error");
    }
    return NULL;
}

void* recv_msg(void* arg)
{
    
    int sock = *((int*)arg);
    char name_msg[NAME_SIZE+BUF_SIZE];
    int str_len;
    while (1)
    {
        
        str_len = read(sock, name_msg, NAME_SIZE+BUF_SIZE-1);
        if(str_len==-1)
        {
            error_handling("read() error");
            return (void*)-1;
        }
        name_msg[str_len] = 0;
        cout << name_msg << endl;
    }
    return NULL;
}


void error_handling(char* message)
{
    cout << message << endl;
    exit(1);
}










