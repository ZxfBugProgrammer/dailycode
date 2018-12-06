#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
const int MAXN=2000;
int tree[MAXN][MAXN];
int book[MAXN][MAXN];

int lowbit(int x)
{
    return x&-x;
}

void Update(int x,int y,int val)
{
    for(int i=x;i<MAXN;i+=lowbit(i))
        for(int j=y;j<MAXN;j+=lowbit(j))
            tree[i][j]+=val;
}

int Query(int x,int y)
{
    int ans=0;
    for(int i=x;i>0;i-=lowbit(i))
        for(int j=y;j>0;j-=lowbit(j))
            ans+=tree[i][j];
    return ans;
}

int main()
{
    int n;
    scanf("%d",&n);
    while(n--)
    {
        char com;
        int t1,t2,t3,t4;
        scanf(" %c %d %d",&com,&t1,&t2);
        t1++,t2++;
        if(com=='B'&&!book[t1][t2])
        {
            Update(t1,t2,1);
            book[t1][t2]=1;
        }
        else if(com=='D'&&book[t1][t2])
        {
            Update(t1,t2,-1);
            book[t1][t2]=0;
        }
        else if(com=='Q')
        {
            scanf("%d %d",&t3,&t4);
            t3++,t4++;
            if(t3>t4)
                swap(t3,t4);
            if(t1>t2)
                swap(t1,t2);
            printf("%d\n",Query(t2,t4)-Query(t1-1,t4)-Query(t2,t3-1)+Query(t1-1,t3-1));
        }
    }
    return 0;
}

