#include"sock.h"

void setAddr(struct sockaddr_in sock_addr, char* argv[])
{
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sock_addr.sin_port = htons(atoi(argv[1]));

}












void error_handling(char* message)
{
    cout << message << endl;
    exit(1);
}




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