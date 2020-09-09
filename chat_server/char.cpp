#include<iostream>
#include<string.h>

#define BUF_SIZE 100

using namespace std;

int main()
{
    int a = 5;
    void* p = (void*)&a;
    int b = *((int*)p);
    cout << b << endl;

    return 0;
}