#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
using namespace std;

#define BUF_SIZE 1024
void error_handling(char* message);

int main(int argc, char*argv[])
{
    int sock;
    char message[BUF_SIZE];
    int str_len;
    sockaddr_in serv_adr;

    if(argc!=3)
    {
        cout << "Usage: " << argv[0] << " <IP> <port>";
        exit(1);
    }

    memset(&serv_adr, 0 , sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        error_handling("connect() error");
    else
        cout << "Connected..." << endl;

    while(1)
    {
        cout << "Input message(Q to quit): ";
        fgets(message, BUF_SIZE, stdin);
        if(!strcmp(message, "q\n")||!strcmp(message,"Q\n"))
            break;
        
        write(sock, message, strlen(message));
        str_len = read(sock, message, BUF_SIZE-1);
        message[str_len] = 0;
        cout << " Message from server: " << message;
    }

    close(sock);
    return 0;

}


void error_handling(char* message)
{
    cout << message << endl;
    exit(1);
}