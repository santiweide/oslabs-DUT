#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>


int num = 0;
pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;

void * add1(void * arg)
{
    int i =0,tmp;
    pthread_mutex_lock(&mylock);
    num ++;
    printf("thread1: number = %d\n",num);
    pthread_mutex_unlock(&mylock);
    
    return ((void*)0);
}
void * add2(void * arg)
{
    int i =0,tmp;
    num ++;
    printf("thread2: number = %d\n",num);
    pthread_mutex_unlock(&mylock);
    return ((void*)0);
}

int main(void)
{
    pthread_t tid1,tid2;
    int err;
    void * tret;
    for(int i =0 ;i < 5;i ++)
    {
        err = pthread_create(&tid1,NULL,add1,NULL);
        if(err != 0)
            exit(-1);
    
        err = pthread_create(&tid2,NULL,add2,NULL);
        if(err != 0)
            exit(-1);
    
        err = pthread_join(tid1,&tret);
        if(err != 0)
            exit(-1);
        err = pthread_join(tid2,&tret);
        if(err != 0)
            exit(-1);
    }
    return 0;

}
