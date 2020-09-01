#include<iostream>
#include<unistd.h>
#include<signal.h>
using namespace std;

//定义型号处理函数（信号处理器）
void timeout(int sig)
{
    if(sig==SIGALRM)
        cout << "Time out" << endl;
    alarm(2);
}


void keycontrol(int sig)
{
    if(sig==SIGINT)
        cout << "CTRL+C pressed" << endl;
    
}

int main(int argc, char* argv[])
{
    int i;
    //注册SIGALARM、SIGINT信号及相应处理器
    signal(SIGALRM, timeout);
    signal(SIGINT, keycontrol);

    //预约2s后发生SIGALARM信号
    alarm(2);

    for(i=0; i<3; i++)
    {
        cout << "wait..." << endl;
        sleep(100);
    }
    return 0;
}
