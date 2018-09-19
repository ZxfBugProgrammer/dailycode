#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector> 
#include <cmath>
#include <map>

using namespace std;
typedef long long ll;
vector<ll> v;
map<ll,ll> vis;

ll Get_sum(ll p,ll n)
{
	v.clear();
	for(ll i=2;i*i<=p;i++)
	{
		if(p%i==0)
		{
			v.push_back(i);
			while(p%i==0)
				p/=i;
		}
	}
	if(p>1)
		v.push_back(p);
	ll tsum=0;
	for(ll i=1;i<(1LL<<v.size());i++)
	{
		ll cnt=0,mul=1;
		for(ll j=0;j<v.size();j++)
		{
			if(i&(1<<j))
			{
				cnt++;
				mul*=v[j];
			}
		}
		ll temp=n/mul;
		if(cnt&1)
			tsum+=(((temp*(temp+1))/2)*mul);
		else
			tsum-=(((temp*(temp+1))/2)*mul);
	}
	return ((n*(n+1))/2)-tsum;
}


int main()
{
	int T;
	scanf("%d",&T);
	ll n,m;
	while(T--)
	{
		vis.clear();
		scanf("%lld %lld",&n,&m);
		ll com,x,y,p;
		while(m--)
		{
			scanf("%lld",&com);
			if(com==1)
			{
				scanf("%lld %lld %lld",&x,&y,&p);
				ll tans=Get_sum(p,y)-Get_sum(p,x-1);
				for(map<ll,ll>::iterator it=vis.begin();it!=vis.end();it++)
				{
					if(x<=it->first&&it->first<=y)
					{
						if(__gcd(it->first,p)==1)
							tans-=it->first;
						if(__gcd(it->second,p)==1)
							tans+=it->second;
					}
				}
				printf("%lld\n",tans);
			}
			else
			{
				scanf("%lld %lld",&x,&p);
				vis[x]=p;
			}
		}
	}
	return 0;
}



