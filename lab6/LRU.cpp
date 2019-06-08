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
        if(len >= maxSize)
        {
            int cnt = min(maxSize,len);
            vector<int> a;
            Node * p = tail;
            while(cnt--)
            {
                a.push_back(p->data);
                p = p->pre;
            }
            bool stop1 = false;
            while(p)
            {
                stack<int> tmp;
                bool stop = false;
                for(int i = 0 ;i < a.size();i ++)
                {
                    if(a[i] == p->data)
                    {
                        tmp.push(a[i]);
                    }
                    if(tmp.size() == maxSize)
                    {
                        Node * q = tail;
                        while(q)
                        {
                            if(q->data == tmp.top())
                            {
                                q->data = x;
                                stop = true;
                                stop1 = true;
                                break;
                            }
                            q = q->pre;
                        }
                    }
                    if(stop)
                        break;
                }
                if(stop1)
                    break;
                p = p->pre;
            }
            if(!p)
            {
                tail->data = x/size;
            }
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
        Node * p = tail;
        int cnt = min(maxSize,len);
        while(cnt --)
        {
            if(p->data == x/size)
                return true;
            p = p->pre;
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
void LRU()
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
    LRU();
    return 0;
}
