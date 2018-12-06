#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;
typedef long long ll;
const ll MOD=1000;

ll qpow(ll a,ll b){
    ll ans=1;
    while(b){
        if(b&1)
            ans=ans*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ans;
}

int main(){
    int T,cas=1;
    scanf("%d",&T);
    while (T--){
        ll n,k;
        scanf("%lld %lld",&n,&k);
        ll ans=(ll)pow(10.0,2.0+fmod(k*log10(n),1.0));
        printf("Case %d: %03lld %03lld\n",cas++,ans,qpow(n,k));
    }
    return 0;
}

