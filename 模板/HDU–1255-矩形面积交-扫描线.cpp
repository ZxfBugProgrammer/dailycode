#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
const int MAXN=10000;
vector<double > v;
struct Edge{
    double l,r,h;
    int f;
    bool operator <(const Edge& a) const{
        return h<a.h;
    }
}edge[MAXN<<1];
struct Tree{
    int l,r;
    double len;
    int f;
}tree[MAXN<<3];

int Get_id(double key)
{
    return lower_bound(v.begin(),v.end(),key)-v.begin()+1;
}

void Build(int l,int r,int cur)
{
    tree[cur].l=l;tree[cur].r=r;tree[cur].f=0;tree[cur].len=0;
    if(l+1==r)
        return;
    int mid=(l+r)>>1;
    Build(l,mid,cur<<1);
    Build(mid,r,cur<<1|1);
}

void Pushup(int cur)
{
    if(tree[cur].f>=1)
        tree[cur].len=v[tree[cur].r-1]-v[tree[cur].l-1];
    else if(tree[cur].l+1==tree[cur].r)
        tree[cur].len=0;
    else
        tree[cur].len=tree[cur<<1].len+tree[cur<<1|1].len;
}

void Update(int l,int r,int val,int cur)
{
    if(l<=tree[cur].l&&tree[cur].r<=r)
    {
        tree[cur].f+=val;
        Pushup(cur);
        return;
    }
    int mid=(tree[cur].l+tree[cur].r)>>1;
    if(l<mid)
        Update(l,r,val,cur<<1);
    if(r>mid)
        Update(l,r,val,cur<<1|1);
    Pushup(cur);
}

double Query(int num,int cur)
{
    if(num+tree[cur].f>=2)
        return tree[cur].len;
    if(tree[cur].l+1==tree[cur].r)
        return 0;
    return Query(num+tree[cur].f,cur<<1)+Query(num+tree[cur].f,cur<<1|1);
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        double xd,yd,xu,yu;
        int cnt=0;
        for(int i=0;i<n;i++)
        {
            scanf("%lf %lf %lf %lf",&xd,&yd,&xu,&yu);
            v.push_back(xd);
            v.push_back(xu);
            edge[cnt].l=xd;edge[cnt].r=xu;edge[cnt].h=yd;edge[cnt++].f=1;
            edge[cnt].l=xd;edge[cnt].r=xu;edge[cnt].h=yu;edge[cnt++].f=-1;
        }
        sort(v.begin(),v.end());
        sort(edge,edge+cnt);
        v.erase(unique(v.begin(),v.end()),v.end());
        double ans=0;
        Build(1,v.size()+100,1);
        for(int i=0;i<cnt-1;i++)
        {
            Update(Get_id(edge[i].l),Get_id(edge[i].r),edge[i].f,1);
            ans+=Query(0,1)*(edge[i+1].h-edge[i].h);
        }
        printf("%.2lf\n",ans);
    }
    return 0;
}

