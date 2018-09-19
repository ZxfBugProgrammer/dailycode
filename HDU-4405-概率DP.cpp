#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;
const int MAXN=100000+10;
double dp[MAXN];
map<int,int> To;

int main()
{
	int n,m;
	while(scanf("%d %d",&n,&m)!=EOF&&!(n==0&&m==0))
	{
		To.clear();
		int from,to;
		for(int i=0;i<m;i++)
		{
			scanf("%d %d",&from,&to);
			To[from]=to;
		}
		dp[n]=0;
		for(int i=n-1;i>=0;i--)
		{
			if(To.find(i)!=To.end())
				dp[i]=dp[To[i]];
			else
			{
				dp[i]=1;
				for(int j=1;j<=6&&i+j<=n;j++)
					dp[i]+=dp[i+j]/6.0;
			}
		}
		printf("%.4f\n",dp[0]);
	} 
	return 0;
}



