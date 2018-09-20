#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
const int MAXN=(int)1e5+10;
int a[MAXN],d[MAXN]; 

int LIS(int n)
{
	d[1]=a[1];
    int len=1;
    for(int i=2;i<=n;i++)
    {
        if(a[i]>=d[len])
            d[++len]=a[i];
        else
        {
            int j=upper_bound(d+1,d+len+1,a[i])-d;
            d[j]=a[i]; 
        }
    }
    return len;
}

int LDS(int n)
{
	d[1]=a[1];
    int len=1;
    for(int i=2;i<=n;i++)
    {
        if(a[i]<=d[len])
            d[++len]=a[i];
        else
        {
            int j=upper_bound(d+1,d+len+1,a[i])-d;
            d[j]=a[i]; 
        }
    }
    return len;
}

int main()
{
	int T;
	scanf("%d",&T);
	int n,k;
	while(T--)
	{
		scanf("%d %d",&n,&k);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		int ans=min(n-LDS(n),n-LIS(n));
		printf(ans<=k?"A is a magic array.\n":"A is not a magic array.\n");
	}
	return 0;
}



