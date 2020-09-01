#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

using namespace std;

void read_childproc(int sig)
{
    int status;
    pid_t id = waitpid(-1, &status, WNOHANG);
    if(WIFEXITED(status))
    {
        cout << "remove proc id: " << id << endl;
        cout << "child send: " << WEXITSTATUS(status) << endl;
    }
}



int main(int argc, char* argv[])
{
    pid_t pid;


    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    
    //注册SIGCHILD处理器
    sigaction(SIGCHLD, &act, 0);

    pid = fork();

    //子进程执行区域
    if(pid==0)
    {
        cout << "I'm child process" << endl;
        sleep(10);
        return 12;
    }

    //父进程执行区域
    else
    {
        sleep(1);
        cout << "child process id: " << pid << endl;
        pid = fork();

        //另一子进程执行区域
        if(pid==0)
        {
            cout << "I'm child process " << endl;
            sleep(10);
            exit(24);
        }

        else
        {
            sleep(1);
            int i;
            cout << "child process id: " << pid << endl;
            for(i=0; i<5; i++)
            {
                cout << "wait..." << endl;
                sleep(5);
            }
        }
        
    }

    return 0;
    




}