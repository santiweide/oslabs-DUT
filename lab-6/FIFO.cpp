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
    bool add_tail(int x)
    {
        if(exist(x))
        {
            return true;
        }
        if(len == maxSize)
        {
            Node * p = head;
            while(p->next)
            {
                p->data = p->next->data;
                p = p->next;
            }
            tail->data = x/size;
        }
        else
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
        }
        return false;
    }
    bool exist(int x)
    {
        Node * p = head;
        while(p)
        {
            if(p->data == x/size)
                return true;
            p = p->next;
        }
        return false;
    }
    void show()
    {
        cout<<">>>";
        Node * p = head;
        while(p)
        {
            cout<<p->data<<" ";
            p = p->next;
        }
        cout<<endl;
    }
};
void FIFO()
{
    int addr;
    List l;
    int n = 0;
    int num = 0;//(n - num)/n
    while(cin>>addr && addr != 0)
    {
        n ++;
        num += l.add_tail(addr);
        l.show();
    }
    cout<<n<<" "<<(float)(n-num)/n<<endl;
}

int main(void)
{
    FIFO();
    return 0;
}
