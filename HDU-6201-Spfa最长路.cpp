#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring> 

using namespace std;
const int MAXN=100000+100;
struct node{
	int to,w,next;
}edge[MAXN<<2];

int cnt,head[MAXN],dis[MAXN];
bool vis[MAXN];

void Init()
{
	memset(vis,0,sizeof(vis));
    memset(head,-1, sizeof(head));
    memset(dis,-1, sizeof(dis));
    cnt=0;
}

void add_edge(int from,int to,int w)
{
    edge[cnt].w=w;
    edge[cnt].to=to;
    edge[cnt].next=head[from];
    head[from]=cnt++;
}

void Spfa(int s)
{
	queue<int> q;
	dis[s]=0;
	q.push(s);
	vis[s]=true;
	while(!q.empty())
	{
		int t=q.front();
		q.pop();
		for(int i=head[t];i!=-1;i=edge[i].next)
		{
			if(dis[edge[i].to]<dis[t]+edge[i].w)
			{
				dis[edge[i].to]=dis[t]+edge[i].w;
				if(!vis[edge[i].to])
				{
					q.push(edge[i].to);
					vis[edge[i].to]=true;
				}
			}
		}
		vis[t]=false;
	}
}

int main()
{
	int T;
	scanf("%d",&T);
	int n;
	while(T--)
	{
		Init();
		scanf("%d",&n);
		int temp;
		int s=n+1,e=n+2;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&temp);
			add_edge(s,i,temp);
			add_edge(i,e,-temp);
		}
		int from,to,w;
		for(int i=1;i<=n-1;i++)
		{
			scanf("%d %d %d",&from,&to,&w);
			add_edge(from,to,-w);
			add_edge(to,from,-w);
		}
		Spfa(s);
		printf("%d\n",dis[e]);
	}
	return 0;
}



