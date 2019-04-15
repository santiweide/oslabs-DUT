#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

double nowTime;
const double timeSlice = 1.0;

typedef struct
{
    unsigned int pid;
    double arriveTime;
    double procTime;
    double startTime;
    double finTime;
    double waitTime;
    double TTime;
    double WTTime;

}dataArea;

typedef struct _node
{
    dataArea * data;
    struct _node * next;
}Node;


typedef struct
{
    Node * head;
    Node * tail;
}List;


List addNode(List pcb, Node * p)
{
    List PCB = pcb;
    if(!PCB.head)
    {
        PCB.head = p;
        PCB.tail = p;
    }else
    {
        PCB.tail->next = p;
        PCB.tail = p;
    }
    return PCB;
}
List initList()
{
    List PCB;
    PCB.head = PCB.tail = NULL;
    return PCB;
}

void show(List PCB)
{
    //printf("\n");
    Node * p = PCB.head;
    if(!p)
        return;
    printf("PID \t ArvTime \t StartTime \t waitTime \t finTime \t TTime \t\t WTTime\n");
    for(;p;p =p -> next)
    {
        printf("%u\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",(p->data->pid),(p->data->arriveTime),(p->data->startTime),(p->data->waitTime),p->data->finTime,p->data->TTime,p->data->WTTime);
    }
    return;
}

void FCFS(const List pcb)
{
    Node * p = pcb.head;
    if(!p)
        return;
    while(p && p->data->finTime != 0.0)
    {
        if(abs(p->data->finTime - nowTime) < 0.01)
        {
            p = p->next;
            break;
        }
        if( p->data->finTime > nowTime)
            return;
        p = p->next;
    }
    if( (p->data->arriveTime < nowTime) || (abs(p->data->arriveTime - nowTime) < 0.01))
    {

        p->data->startTime = nowTime;
        p->data->finTime = p->data->startTime + p->data->procTime;
        p->data->waitTime = p->data->startTime - p->data->arriveTime;
        p->data->TTime = p->data->waitTime + p->data->procTime;
        p->data->WTTime = p->data->TTime / p->data->procTime;
    }
}
#define flg 23333.0
void SJF(const List pcb)
{
    Node * p = pcb.head;
    if(!p)
        return;

    double minData = flg;
    Node * tmp = NULL;
    for(;p;p = p->next)
    {
        if( p->data->finTime > nowTime && abs(p->data->finTime - nowTime) > 0.01)
                return;

        if(p->data->finTime == 0.0 && p->data->procTime < minData)
        {
            minData = p->data->procTime;
            tmp = p;
        }
    }
    if( (tmp->data->arriveTime < nowTime) || (abs(tmp->data->arriveTime - nowTime) < 0.01))
    {
        tmp->data->startTime = nowTime;
        tmp->data->finTime = tmp->data->startTime + tmp->data->procTime;
        tmp->data->waitTime = tmp->data->startTime - tmp->data->arriveTime;
        tmp->data->TTime = tmp->data->waitTime + tmp->data->procTime;
        tmp->data->WTTime = tmp->data->TTime / tmp->data->procTime;
    }

}

double arriveTimeAdd[] = {0,1,2,3,6,7,9,11,12,13,14,20,23,24,25,26};
double procTimeAdd[] = {1,35,10,5,9,21,35,23,42,1,7,5,3,22,31,1};
unsigned int pidAdd[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int nextP = 0;
int maxP = 16;

int main()
{
    List PCB = initList();
    scanf("%lf",&nowTime);
    while(nowTime < 250.0)
    {
        printf("%lf\n",nowTime);
        if(nextP < maxP && (abs(nowTime - arriveTimeAdd[nextP]) < 0.01))
        {
            Node * p = (Node*)malloc(sizeof(Node));
            p->data = (dataArea*)malloc(sizeof(dataArea));
            p->data->arriveTime = arriveTimeAdd[nextP];
            p->data->procTime = procTimeAdd[nextP];
            p->data->pid = pidAdd[nextP];
            p->data->finTime = p->data->startTime = p->data->TTime = p->data->WTTime = p->data->waitTime = 0.0;
            p->next = NULL;
            PCB = addNode(PCB,p);
            nextP ++;
        }
        FCFS(PCB);
        //SJF(PCB);
        show(PCB);
        //Sleep(200);
        //system("pause");
        nowTime += timeSlice;
    }
    return 0;
}
