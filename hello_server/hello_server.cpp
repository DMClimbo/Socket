#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
void error_handling(char *message);
using namespace std;



int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;

    //定义服务器和客户端的地址及内存大小
    sockaddr_in serv_addr;
    sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[] = "Hello World!";

    if(argc!=2)
    {
        cout << " Usage: " << argv[0] << " <port>" << endl;
        exit(1);
    }

    //创建服务端套接字，失败则抛出异常
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0 , sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    //绑定本地ip地址和端口号
    if(bind(serv_sock, (sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
        error_handling("bind() error");
    

    //将套接字转化为可接受状态
    if(listen(serv_sock,5)==-1)
        error_handling("listen() error");

    //
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (sockaddr*) &clnt_addr_size, &clnt_addr_size);
    if(clnt_sock==-1)
        error_handling("accept() error");
    
    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);

    return 0;



}