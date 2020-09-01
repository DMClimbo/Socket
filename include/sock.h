#ifndef _SOCK_H_
#define _SOCK_H_
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<sys/socket.h>
using namespace std;

//套接字地址初始化
void setAddr(struct sockaddr_in sock_addr, char* argv[]);















//异常处理
void error_handling(char* message);





//注册SIGCHILD信号对应的处理器
void read_childproc(int sig);





#endif