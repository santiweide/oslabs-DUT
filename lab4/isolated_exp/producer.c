#include "ipc.h"
int main(int argc,char *argv[])
{
    int rate;
    
    //可在在命令行第一参数指定一个进程睡眠秒数,以调解进程执行速度
    if(argv[1] != NULL) rate = atoi(argv[1]);
    else rate = 3; //不指定为 3 秒
     
    buff_key = 101;//缓冲区任给的键值
    buff_num = 8;//缓冲区任给的长度
    pput_key = 102;//生产者放产品指针的键值
    pput_num = 1; //指针数
    
    shm_flg = IPC_CREAT | 0644;//共享内存读写权限
    //获取缓冲区使用的共享内存,buff_ptr 指向缓冲区首地址
    buff_ptr = (char *)set_shm(buff_key,buff_num,shm_flg);
    //获取生产者放产品位置指针 pput_ptr
    pput_ptr = (int *)set_shm(pput_key,pput_num,shm_flg);
    
    //信号量使用的变量
    ofr1_key = 201;
    ofr2_key = 202;
    ofr3_key = 301;
    fin_key = 302;
    sem_flg = IPC_CREAT | 0644;
    
    int random;

    sem_val = 0;
    ofr1_sem = set_sem(ofr1_key,sem_val,sem_flg);
    
    sem_val = 0;
    ofr2_sem = set_sem(ofr2_key,sem_val,sem_flg);
    
    sem_val = 0;
    ofr3_sem = set_sem(ofr3_key,sem_val,sem_flg);
    
    sem_val = 0;
    fin_sem = set_sem(fin_key,sem_val,sem_flg);
       
  
    while(1){
        random = rand() % 3;
        
        if(random == 0)
          up(ofr1_sem);
        else if(random == 1)
          up(ofr2_sem);
        else 
          up(ofr3_sem);
        
        buff_ptr[*pput_ptr] = 'A'+ random;
        sleep(rate);
        printf("%d producer put: %c to Buffer[%d]\n",getpid(),buff_ptr[*pput_ptr],*pput_ptr);
        //存放位置循环下移
        *pput_ptr = (*pput_ptr+1) % buff_num;
           
        down(fin_sem);    
    }       
    return EXIT_SUCCESS;
}


