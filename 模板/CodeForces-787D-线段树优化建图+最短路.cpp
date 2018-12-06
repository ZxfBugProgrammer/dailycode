/*
@resouces: codeforces 787D
@date: 2017-3-27
@author: QuanQqqqq
@algorithm: 线段树 + dijkstra nlogn 
*/
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define MAXN 500005
#define ll long long

using namespace std;

const ll LLINF = 0x3f3f3f3f3fLL;
typedef pair<ll,int> pli;

struct Edge{
    int to,weight;
    Edge(int _to = 0,int _weight = 0) : to(_to),weight(_weight){}
};

priority_queue<pli > Q;
vector<vector<Edge> > G(MAXN);
bool vis[MAXN];
int id[MAXN][2];
vector<int> vs;
ll d[MAXN];
int idx;

void addEdge(int from,int to,int weight){
    G[from].push_back(Edge(to,weight));
}

void build(int l,int r,int rt,int wh){  //wh0为从上到下的线段树，wh1为从下到上的线段树 
    id[rt][wh] = ++idx;
    if(l == r){
        if(wh == 0){
            addEdge(id[rt][wh],l,0);
        } else {
            addEdge(l,id[rt][wh],0);
        }
        return;
    }
    int mid = l + r >> 1;
    build(l,mid,rt << 1,wh);
    build(mid + 1,r,rt << 1 | 1,wh);
    if(wh == 0){
        addEdge(id[rt][wh],id[rt << 1][wh],0);
        addEdge(id[rt][wh],id[rt << 1 | 1][wh],0);
    } else {
        addEdge(id[rt << 1][wh],id[rt][wh],0);
        addEdge(id[rt << 1 | 1][wh],id[rt][wh],0);
    }
}

void get(int l,int r,int L,int R,int rt,int wh){
    if(L <= l && r <= R){
        vs.push_back(id[rt][wh]);
        return;
    }
    int m = l + r >> 1;
    if(m >= L){
        get(l,m,L,R,rt << 1,wh);
    }
    if(m < R){
        get(m + 1,r,L,R,rt << 1 | 1,wh);
    }
}

void dijkstra(int s,int n){
    for(int i = 1;i <= n;i++){
        vis[i] = false;
        d[i] = LLINF;
    }
    Q.push({-0,s});
    d[s] = 0;
    while(!Q.empty()){
        int u = Q.top().second;
        Q.pop();
        if(vis[u]){
            continue;
        }
        vis[u] = true;
        for(int i = 0;i < G[u].size();i++){
            Edge e = G[u][i];
            int v = e.to,w = e.weight;
            if(w + d[u] < d[v]){
                d[v] = w + d[u];
                Q.push({-d[v],v});
            }
        }
    }
}

void init(int n){
    while(!Q.empty()){
        Q.pop();
    }
    for(int i = 1;i <= n;i++){
        G[i].clear();
    }
}

int main(){
    int n,q,s,l,r,t,u,v,c;
    scanf("%d %d %d",&n,&q,&s);
    init(n * 5);
    idx = n;
    build(1,n,1,0);
    build(1,n,1,1);
    while(q--){
        scanf("%d %d",&t,&u);
        if(t == 1){
            scanf("%d %d",&v,&c);
            addEdge(u,v,c);
        } else if(t == 2) {
            vs.clear();
            scanf("%d %d %d",&l,&r,&c);
            get(1,n,l,r,1,0);
            for(int i = 0;i < vs.size();i++){
                addEdge(u,vs[i],c);
            }
        } else {
            vs.clear();
            scanf("%d %d %d",&l,&r,&c);
            get(1,n,l,r,1,1);
            for(int i = 0;i < vs.size();i++){
                addEdge(vs[i],u,c);
            }
        }
    }
    dijkstra(s,5 * n);
    for(int i = 1;i <= n;i++){
        if(d[i] == LLINF){
            d[i] = -1;
        }
        printf("%lld ",d[i]);
    }
}

