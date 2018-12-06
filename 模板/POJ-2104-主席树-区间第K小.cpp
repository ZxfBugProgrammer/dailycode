#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
 
using namespace std;
const int MAXN=1e5+10;
struct Tree{
    int l,r,sum;
}T[MAXN*40];
vector<int> v;
int cnt,root[MAXN],a[MAXN];
 
void Init()
{
    cnt=0;
    T[cnt].l=0;T[cnt].r=0;T[cnt].sum=0;
    root[cnt]=0;
    v.clear();
}
 
int getid(int x)
{
    return lower_bound(v.begin(),v.end(),x)-v.begin()+1;
}
 
void Update(int l,int r,int &x,int y,int pos)
{
    T[++cnt]=T[y],T[cnt].sum++,x=cnt;
    if(l==r)
        return;
    int mid=(l+r)>>1;
    if(mid>=pos)
        Updata(l,mid,T[x].l,T[y].l,pos);
    else
        Updata(mid+1,r,T[x].r,T[y].r,pos);
}
 
int Query(int l,int r,int x,int y,int k)
{
    if(l==r)
        return l;
    int mid=(l+r)>>1;
    int sum=T[T[y].l].sum-T[T[x].l].sum;
    if(sum>=k)
        return Query(l,mid,T[x].l,T[y].l,k);
    else
        return Query(mid+1,r,T[x].r,T[y].r,k-sum);
}
 
int main()
{
    Init();
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        v.push_back(a[i]);
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    for(int i=1;i<=n;i++)
        Updata(1,n,root[i],root[i-1],getid(a[i]));
    int l,r,k;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&l,&r,&k);
        printf("%d\n",v[Query(1,n,root[l-1],root[r],k)-1]);
    }
    return 0;
}

