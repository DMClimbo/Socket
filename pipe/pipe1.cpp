#include<iostream>
#include<unistd.h>

#define BUF_SIZE 30
using namespace std;

int main(int argc, char* argv[])
{
    int fds[2];
    char str[] = "Who are you ?";
    char buf[BUF_SIZE];
    pid_t pid;

    pipe(fds);
    pid = fork();

    //子进程
    if(pid==0)
    {
        write(fds[1], str, sizeof(str));
    }

    //父进程
    else
    {
        read(fds[0], buf, BUF_SIZE);
        cout << buf << endl;
    }

    return 0;
    


}