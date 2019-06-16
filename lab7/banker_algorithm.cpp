#include <bits/stdc++.h>
using namespace std;

class Banker
{
public:
    Banker(int n,int m)
    {
        this->n = (n > 0)?n:0;
        this->m = (m > 0)?m:0;
        Allocation =(int **)malloc(sizeof(int*)*this->n);
        Max = (int **)malloc(sizeof(int*)*this->n);
        Need = (int **)malloc(sizeof(int*)*this->n);
        Avaliable = new int [this->m];
        for(int i = 0;i < this->n;i ++)
        {
            Allocation[i] = (int *)malloc(sizeof(int)*this->m);
            Max[i] = (int *)malloc(sizeof(int)*this->m);
            Need[i] = (int *)malloc(sizeof(int)*this->m);
        }
    }
    void init()
    {
        for(int i = 0;i < n;i ++)
        {
            for(int j =0 ;j < m;j ++)
            {
                int x;
                cin>>x;
                Allocation[i][j] = x;
            }
        }
        for(int i = 0;i < n;i ++)
        {
            for(int j =0 ;j < m;j ++)
            {
                int x;
                cin>>x;
                Max[i][j] = x;
            }
        }
        for(int i = 0;i < m;i ++)
        {
            int x;
            cin>>x;
            Avaliable[i] = x;
        }

        for(int i  =0 ;i < n;i ++)
        {
            for(int j  =0;j < m;j ++)
            {
                Need[i][j] = Max[i][j] - Allocation[i][j];
            }
        }
    }
    bool safety_check()
    {
        int * Work = new int [m];
        for(int i = 0;i < m;i ++)
            Work[i] = Avaliable[i];



        bool * all_ok = new bool [n];
        for(int i =0 ;i <m;i ++)
            all_ok[i] = false;
        int cnt = m * n * n;

        while(cnt --)
        {
            bool fin = true;
            for(int i =0 ;i < m;i ++)
                if(all_ok[i] == false)
                {
                    fin = false;
                    break;
                }
            if(fin)
            {
                return true;
            }
            for(int i = 0;i < n; i++)
            {
                if(all_ok[i])
                    continue;
                bool flg = true;
                for(int j =0 ;j < m;j ++)
                {
                    if(Need[i][j] > Work[j])
                    {
                        flg = false;
                        break;
                    }
                }
                if(flg)
                {
                    all_ok[i] = true;
                    for(int j =0 ;j <m;j ++)
                        Work[j] += Allocation[i][j];
                    break;
                }
            }
        }
        return false;
    }
    bool request_check(int * & request, int numI)
    {
        if(!safety_check())
            return false;
        bool ok = true;
        for(int i = 0;i < m;i ++)
        {
            if(request[i] > Need[numI][i])
            {
                ok = false;
                break;
            }
        }
        if(!ok)
        {
            cout<<"Over Max request!!!\n";
            return false;
        }
        ok = true;
        for(int i = 0;i < m;i ++)
        {
            if(request[i] > Avaliable[i])
            {
                ok = false;
                break;
            }
        }
        if(!ok)
        {
            cout<<"Over Avaliable!!!\n";
            return false;
        }
        for(int i =0 ;i<m;i ++)
        {
            Avaliable[i] -= request[i];
            Allocation[numI][i] += request[i];
            Need[numI][i] -= request[i];
        }
        return safety_check();
    }
    void showNeed()
    {
        cout<<"Need:\n";
        for(int i =0 ;i <n;i ++)
        {
            for(int j =0 ;j < m;j ++)
            {
                cout<<Need[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    void showAllocation()
    {
        cout<<"Allocation:\n";
        for(int i =0 ;i <n;i ++)
        {
            for(int j =0 ;j < m;j ++)
            {
                cout<<Allocation[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    void showMax()
    {
        cout<<"Max:\n";
        for(int i =0 ;i <n;i ++)
        {
            for(int j =0 ;j < m;j ++)
            {
                cout<<Max[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    void showAvaliable()
    {
        cout<<"Avaliable:\n";
        for(int i =0 ;i < m;i ++)
            cout<<Avaliable[i]<<" ";
        cout<<endl;
    }
private:
    /**
    * n procedures, m kinds of resources
    */
    int n;
    int m;
    /**Need Array**/
    int ** Need;
    int **Allocation;
    int **Max;
    int * Avaliable;
};

int main()
{
    int n = 5,m = 3;
    Banker banker(n,m);
    banker.init();
    cout<<"---"<<banker.safety_check();
    banker.showAllocation();
    banker.showMax();
    banker.showNeed();
    banker.showAvaliable();


    int * p = new int [m];
    int line;
    cin>>line;
    for(int i =0 ;i < m;i ++)
        cin>>p[i];
    cout<<"---"<<banker.request_check(p,line);
    banker.showAvaliable();
    banker.showAllocation();
    banker.showMax();
    banker.showNeed();

    return 0;
}

/**
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

3 3 2

4 3 3 0

**/
