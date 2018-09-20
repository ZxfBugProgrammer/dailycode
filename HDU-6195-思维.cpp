#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long ll; 

int main()
{
	ll m,k;
	while(scanf("%lld %lld",&m,&k)!=EOF)
	{
		ll ans=k+(m-k)*k;
		printf("%lld\n",ans);
	}
	return 0;
}



