#include <iostream>
#include <bits/stdc++.h>
using namespace std;

const int size = 100;
const int maxSize = 3;
struct Node
{
    int data;
    Node * next;
    Node * pre;
    Node(int x = -1)
    {
        data = x / size;
        next = pre = NULL;
    }
};

struct List
{
    int len;
    Node * head;
    Node * tail;
    List()
    {
        head = tail = NULL;
        len = 0;
    }
    bool add_tail(int x, bool con)
    {
        if(maxSize > len || con)
        {
            Node * p = new Node(x);
            if(!head)
            {
                head = tail = p;
            }
            else
            {
                p->pre = tail;
                tail->next = p;
                tail = p;
            }
            len ++;
            return false;
        }
        else//maxSize ... len中第一次出现最晚的
        {
            if(exist(x))
            {
                return true;
            }
            int cnt = maxSize;
            Node * p = head;
            vector<int> a;
            while(cnt --)
            {
                a.push_back(p->data);
                p = p->next;
            }
            int * rank = new int [maxSize];
            for(Node * q = p;q;q = q->next)
            {
                bool flg = false;
                for(int i = 0;i < maxSize;i ++)
                {
                    if(a[i] == q->data)
                    {
                        rank[i] = q-p;
                        flg = true;
                        break;
                    }
                }
                if(flg)
                    break;
            }
            int mini = 0;
            for(int i = 1;i < maxSize;i ++)
            {
                if(a[mini] > a[i])
                    mini = i;
            }
            (p+mini)->data = x;
            //show();
            return false;
        }
    }
    bool exist(int x)
    {
        Node * p = head;
        int cnt = 0;
        while(cnt < min(maxSize,len))
        {
            if(p->data == x/size)
                return true;
            p = p->next;
            cnt ++;
        }
        return false;
    }
    void show()
    {
        cout<<">>>";
        Node * p = tail;
        int cnt = min(maxSize,len);
        while(cnt --)
        {
            cout<<p->data<<" ";
            p = p->pre;
        }
        cout<<endl;
    }
};
void OPT()
{
    int addr;
    List l;
    int num = 0;//(n - num)/n
    vector<int> v;
    while(cin>>addr && addr != 0)
    {
        v.push_back(addr);
        l.add_tail(addr,true);
    }
    for(int i =0 ;i < v.size();i ++)
    {
        num += l.add_tail(v[i],false);
    }
    cout<<num<<" "<<(float)(v.size()-num)/v.size()<<endl;
}

int main(void)
{
    OPT();
    return 0;
}
