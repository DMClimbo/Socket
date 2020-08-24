#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

using namespace std;
#define BUF_SIZE 30
void error_handling(char * message);

int main(int argc , char* argv[])
{
    int sd;
    FILE *fp;

    char buf[BUF_SIZE];
    int read_cnt;
    sockaddr_in serv_adr;
    if(argc!=3)
    {
        cout << "Usage:" << argv[0] << "<IP><port>";
        exit(1);
    }

    fp = fopen("receive.txt", "wb");

    //创建套接字
    sd = socket(PF_INET, SOCK_STREAM, 0);
    if(sd==-1)
        error_handling("socket() error");

    //初始化服务端套接字地址信息
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    //连接服务端
    if(connect(sd, (sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        error_handling("connect() error");
    
    //当输入缓冲中还有数据时持续写入
    while((read_cnt = read(sd, buf, BUF_SIZE))!=0)
        fwrite((void*)buf, 1, read_cnt, fp);
    
    cout << "Received file data" << endl;
    write(sd, "Thank you" , 10);

    //关闭文件和套接字
    fclose(fp);
    close(sd);
    return 0;
    




}





void error_handling(char* message)
{
    cout << message << endl;
    exit(1);
}