#include<iostream>
#include<stdlib.h>
#include<string>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
using namespace std;
void error_handling(char *message);

int main(int argc, char* argv[])
{
    int sock;
    sockaddr_in serv_addr;
    char message[30];
    int str_len;

    if(argc!=3)
    {
        cout << "Usage: " << argv[0] << "<IP> <port>" << endl;
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock==-1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atio(argv[2]));

    if(connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("connect() error");
    
    str_len = read(sock, message, sizeof(message)-1);
    if(str_len==-1)
        error_handling("read() error");
    
    cout << " Message from serve: " << message << endl;
    close(sock);
    return 0;
    

}