#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
const int MAXN=1000000+10;
const int MAXE=5000000+10;
const int INF=0x3f3f3f3f;
struct node{
    int to,w,next;
    bool operator < (const node &a) const
    {
        return w>a.w;
    }
}edge[MAXE];
int cnt,head[MAXN],dis[MAXN];
bool vis[MAXN];

void Init()
{
    memset(head,-1, sizeof(head));
    memset(dis,INF, sizeof(dis));
    cnt=0;
}

void add_edge(int from,int to,int w)
{
    edge[cnt].w=w;
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void Dijkstra(int s)
{
    priority_queue<node> q;
    node t1,t2;
    t1.to=s,t1.w=0;
    q.push(t1);
    dis[s]=0;
    while(!q.empty())
    {
        t1=q.top();
        q.pop();
        int u=t1.to;
        if(vis[u])
            continue;
        vis[u]=true;
        for(int i=head[u];i!=-1;i=edge[i].next)
        {
            int v=edge[i].to;
            if(!vis[v]&&dis[v]>dis[u]+edge[i].w)
            {
                dis[v]=dis[u]+edge[i].w;
                t2.to=v;t2.w=dis[v];
                q.push(t2);
            }
        }
    }
}

int main()
{
    Init();
    int n,m,k,s,t;
    scanf("%d %d %d %d %d",&n,&m,&k,&s,&t);
    s++,t++;
    int from,to,w;
    for(int i=0;i<m;i++)
    {
        scanf("%d %d %d",&from,&to,&w);
        from++,to++;
        for(int j=0;j<=k;j++)
        {
            add_edge(from+j*n,to+j*n,w);
            add_edge(to+j*n,from+j*n,w);
            if(j!=k)
            {
                add_edge(from+j*n,to+(j+1)*n,0);
                add_edge(to+j*n,from+(j+1)*n,0);
            }
        }
    }
    Dijkstra(s);
    int ans=INF;
    for(int i=0;i<=k;i++)
        ans=min(ans,dis[t+i*n]);
    printf("%d\n",ans);
    return 0;
}
