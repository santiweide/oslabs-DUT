#include "ipc.h"
int main(int argc,char *argv[])
{
    int rate;
    //可在在命令行第一参数指定一个进程睡眠秒数,以调解进程执行速度
    if(argv[1] != NULL) rate = atoi(argv[1]);
    else rate = 3; //不指定为 3 秒
    
    //共享内存 使用的变量
    buff_key = 101; //缓冲区任给的键值
    buff_num = 8; //缓冲区任给的长度
    cget_key = 103; //消费者取产品指针的键值
    cget_num = 1; //指针数
    shm_flg = IPC_CREAT | 0644; //共享内存读写权限
    
    //获取缓冲区使用的共享内存,buff_ptr 指向缓冲区首地址
    buff_ptr = (char *)set_shm(buff_key,buff_num,shm_flg);
    //获取消费者取产品指针,cget_ptr 指向索引地址
    cget_ptr = (int *)set_shm(cget_key,cget_num,shm_flg);
    
    //信号量使用的变量
    ofr1_key = 201; //生产者同步信号灯键值
    ofr2_key = 202; //生产者互斥信号灯键值
    ofr3_key = 301; //消费者同步信号灯键值
    fin_key = 302; //消费者互斥信号灯键值
    sem_flg = IPC_CREAT | 0644; //信号灯操作权限
   
    sem_val = 0;
    ofr1_sem = set_sem(ofr1_key,sem_val,sem_flg);    
    
    sem_val = 0;
    ofr2_sem = set_sem(ofr2_key,sem_val,sem_flg);     
    
    sem_val = 0;
    ofr3_sem = set_sem(ofr3_key,sem_val,sem_flg);
     
    sem_val = 0;
    fin_sem = set_sem(fin_key,sem_val,sem_flg);

    while(1){
        down(ofr3_sem);
        
        sleep(rate);
        printf("%dconsumer1 get C: %c from Buffer[%d]\n",getpid(),buff_ptr[*cget_ptr],*cget_ptr);
        //读取位置循环下移
        *cget_ptr = (*cget_ptr+1) % buff_num;
                
        up(fin_sem);
    }
    return EXIT_SUCCESS;
}
