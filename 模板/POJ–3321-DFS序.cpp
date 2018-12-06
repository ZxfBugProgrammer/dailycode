#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int MAXN=(int)1e5+10;
struct node{
    int to,next;
}edge[2*MAXN];
int head[MAXN],in[MAXN],out[MAXN];
int cnt=0,tot=0;
int c[MAXN];
bool vis[MAXN];

void add_edge(int from,int to)
{
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void dfs(int cur,int pre)
{
    in[cur]=++tot;
    for(int i=head[cur];i!=-1;i=edge[i].next)
        if(edge[i].to!=pre)
            dfs(edge[i].to,cur);
    out[cur]=tot;
}

int lowbit(int x)
{
    return (-x)&x;
}


void add(int x,int n,int val)
{
    while(x<=n)
    {
        c[x]+=val;
        x+=lowbit(x);
    }
}

int sum(int x)
{
    int ans=0;
    while(x)
    {
        ans+=c[x];
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    memset(head,-1,sizeof(head));
    int n;
    scanf("%d",&n);
    int u,v;
    for(int i=0;i<n-1;i++)
    {
        scanf("%d %d",&u,&v);
        add_edge(u,v);
        add_edge(v,u);
    }
    for(int i=1;i<=n;i++)
    {
        vis[i]=true;
        add(i,n,1);
    }
    dfs(1,0);
    int m,temp;
    char com;
    scanf("%d",&m);
    while (m--)
    {
        scanf(" %c %d",&com,&temp);
        if(com=='Q')
            printf("%d\n",sum(out[temp])-sum(in[temp]-1));
        else
        {
            if(vis[in[temp]])
            {
                add(in[temp],n,-1);
                vis[in[temp]]=false;
            }
            else
            {
                add(in[temp],n,1);
                vis[in[temp]]=true;
            }
        }
    }
    return 0;
}

