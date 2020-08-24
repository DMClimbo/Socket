#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 30
using namespace std;
void error_handling(char* message);

int main(int argc, char* argv[])
{
    
    int serv_sd, clnt_sd;
    FILE* fp;
    char buf[BUF_SIZE];
    int read_clnt;
    sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_adr_sz;

    if(argc!=2)
    {
        cout << "Usage: " << argv[0] << "<port>" << endl;
        exit(1);
    }

    fp = fopen("file_server.cpp", "rb");

    //创建服务端套接字
    serv_sd = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sd==-1)
        error_handling("socket() error");

    //初始化服务端套接字地址信息
    memset(&serv_addr, 0 , sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    //绑定套接字
    if((bind(serv_sd, (sockaddr*)&serv_addr, sizeof(serv_addr)))==-1)
        error_handling("bind() error");

    //开始监听
    if((listen(serv_sd, 5))==-1)
        error_handling("listen() error");

    //客户端连接成功则创建一个新的套接字进行通信
    clnt_adr_sz = sizeof(clnt_addr);
    clnt_sd = accept(serv_sd, (sockaddr*)&clnt_addr, &clnt_adr_sz);
    if(clnt_sd==-1)
        error_handling("accept() error");

    while(1)
    {
        read_clnt = fread((void*)buf, 1, BUF_SIZE, fp);
        if(read_clnt<BUF_SIZE)
        {
            write(clnt_sd, buf, read_clnt);
            break;
        }
        write(clnt_sd, buf, BUF_SIZE);
    }

    //对输入流进行半关闭
    shutdown(clnt_sd, SHUT_WR);
    read(clnt_sd, buf, BUF_SIZE);
    cout << "Message from client: " << buf << endl;

    //关闭文件和套接字
    fclose(fp);
    close(clnt_sd);
    close(serv_sd);
    return 0;





}



void error_handling(char* message)
{
    cout << message << endl;
    exit(1);
}