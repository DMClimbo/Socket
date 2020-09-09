#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

using namespace std;
void*  thread_main(void* arg);

int main(int argc, char* argv[])
{
    pthread_t t_id;
    int  thread_param=5;
    void* thr_ret;

    if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_param)!=0)
    {
        cout << "pthread_create()  error" << endl;
        return -1;
    }

    if(pthread_join(t_id, &thr_ret)!=0)
    {
        cout << "pthread_join() error" << endl;
        return -1;
    }

    cout << "Thread  return message: " << (char*)thr_ret << endl;
    free(thr_ret);
    return 0;

}



void* thread_main(void* arg)
{
    int i;
    int cnt = *((int*)arg);
    char* msg = (char*)malloc(sizeof(char)*50);
    strcpy(msg, "Hello, I'm thread~");
    for(i=0; i<cnt; i++)
    {
        sleep(1);
        cout << "running thread" << endl;
    }
    return (void*)msg;
}