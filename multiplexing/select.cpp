#include<iostream>
#include<unistd.h>
#include<sys/time.h>
#include<sys/wait.h>
#define BUF_SIZE 30
using namespace std;

int main(int argc, char* argv[])
{
    fd_set reads, temps;
    int result, str_len;
    char buf[BUF_SIZE];
    struct timeval timeout;

    //初始化fd_set变量，将文件描述符0对应的为设置为1，即监视标准输入的变化
    FD_ZERO(&reads);
    FD_SET(0, &reads);

    while(1)
    {
        //将初始变量复制到temps变量中
        temps = reads;

        //调用select函数后，timeval的成员值将替换为超时前剩余时间，因此每次调用函数前都需要初始化
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;

        //调用select函数，如果有控制台输入数据，返回大于0的数，如果没有而引发超时，则返回0
        result = select(1, &temps, 0, 0, &timeout);
        if(result==-1)
        {
            cout << "select() error" << endl;
            break;
        }

        else if(result==0)
            cout << "Time-out" << endl;

        else
        {
            if(FD_ISSET(0, &temps))
            {
                str_len = read(0, buf, BUF_SIZE);
                buf[str_len] = 0;
                cout << "Message from console: " << buf << endl;
            }
        }
        


    }
    return 0;

}