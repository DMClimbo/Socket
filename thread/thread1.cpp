#include<iostream>
#include<pthread.h>
#include<unistd.h>

using namespace std;
void* thread_main(void* arg);

int main(int argc, char* argv[])
{
    pthread_t  t_id;
    int thread_param = 5;

    if(pthread_create(&t_id,  NULL, thread_main,  (void*)&thread_param)!=0)
    {
        cout << "pthread() error" << endl;
        return -1;
    }
    sleep(10);
    cout << "end of main" << endl;
    return 0;

}


void * thread_main(void* arg)
{
    int i;
    int cnt = *((int*)arg);
    for(i=0; i<cnt; i++)
    {
        sleep(1);
        cout << "running thread" << endl;
    }
    return NULL;

}