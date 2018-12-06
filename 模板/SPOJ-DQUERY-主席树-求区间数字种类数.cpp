#include <cstdio>
#include <algorithm>
#include <iostream>
#include <map>
 
using namespace std;
const int MAXN=30010;
struct node{
    int l,r,sum;
}T[MAXN*40];
int cnt,a[MAXN],root[MAXN];
map<int,int> pos;
 
void Init()
{
    cnt=0;
    T[cnt].l=0;T[cnt].r=0;T[cnt].sum=0;
    root[cnt]=0;
    pos.clear();
}
 
void Update(int l,int r,int &now,int pre,int pos,int add)
{
    T[++cnt]=T[pre];T[cnt].sum+=add;now=cnt;
    if(l==r)
        return;
    int mid=(l+r)>>1;
    if(pos<=mid)
        Update(l,mid,T[cnt].l,T[pre].l,pos,add);
    else
        Update(mid+1,r,T[cnt].r,T[pre].r,pos,add);
}
 
int Query(int l,int r,int root,int left)
{
    if(l>=left)
        return T[root].sum;
    int mid=(l+r)>>1;
    if(mid>=left)
        return Query(l,mid,T[root].l,left)+T[T[root].r].sum;
    else
        return Query(mid+1,r,T[root].r,left);
}
 
int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        Init();
        int temp;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            if(!pos.count(a[i]))//Ö±½Ó¼Ó
            {
                Update(1,n,root[i],root[i-1],i,1);
            }
            else
            {
                Update(1,n,temp,root[i-1],pos[a[i]],-1);
                Update(1,n,root[i],temp,i,1);
            }
            pos[a[i]]=i;
        }
        int q,l,r;
        scanf("%d",&q);
        for(int i=0;i<q;++i)
        {
            scanf("%d%d",&l,&r);
            printf("%d\n",Query(1,n,root[r],l));
        }
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <cstring>
 
using namespace std;
const int maxn=30000+5;
map<int,int> mp;
int data[maxn],a[maxn],ans[200000+5];
struct node{
    int l,r,id;
    bool operator<(node t)const{
        return r<t.r;
    }
}q[200000+5];
 
int lowbit(int x)
{
    return x&-x;
}
 
int Get_sum(int i)
{
    int ans=0;
    while(i>0){
        ans+=data[i];
        i-=lowbit(i);
    }
    return ans;
}
 
void Update(int i,int x)
{
    while(i<maxn){
        data[i]+=x;
        i+=lowbit(i);
    }
}
 
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        memset(data,0,sizeof(data));
        mp.clear();
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        int m;
        scanf("%d",&m);
        for(int i=0;i<m;i++)
        {
            scanf("%d%d",&q[i].l,&q[i].r);
            q[i].id=i;
        }
        sort(q,q+m);
        int pre=1;
        for(int i=0;i<m;i++)
        {
            for(int j=pre;j<=q[i].r;j++)
            {
                if(mp[a[j]]!=0)
                    Update(mp[a[j]],-1);
                Update(j,1);
                mp[a[j]]=j;
            }
            pre=q[i].r+1;
            ans[q[i].id]=Get_sum(q[i].r)-Get_sum(q[i].l-1);
        }
        for(int i=0;i<m;i++)
            printf("%d\n",ans[i]);
    }
    return 0;
}

