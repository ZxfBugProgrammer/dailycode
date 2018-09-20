#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=2;
const ll MOD=998244353;

struct Matrix{
    ll a[MAXN][MAXN];
    void init(){
        memset(a,0,sizeof(a));
        for(int i=0;i<MAXN;i++)
            a[i][i]=1;
    }
};

Matrix mul(Matrix a, Matrix b)
{
    Matrix ans;
    for(int i=0;i<MAXN;i++)
    {
        for(int j=0;j<MAXN;j++)
        {
            ans.a[i][j]=0;
            for(int k=0;k<MAXN;k++)
                ans.a[i][j]=(ans.a[i][j]+(a.a[i][k]*b.a[k][j])%MOD)%MOD;
        }
    }
    return ans;
}

Matrix qpow(Matrix a, ll n)
{
    Matrix ans;
    ans.init();
    while(n)
    {
        if(n&1)
            ans = mul(ans, a);
        a=mul(a,a);
        n>>=1;
    }
    return ans;
}

int main()
{
    ll n;
    while(scanf("%lld",&n)!=EOF)
    {
    	n=2*n+3;
        Matrix a;
        a.a[0][0]=1;a.a[0][1]=1;
        a.a[1][0]=1;a.a[1][1]=0;

        Matrix s;
        s.a[0][0]=1;
        s.a[1][0]=0; 

        Matrix ans=qpow(a,n);
        ans=mul(ans,s);
        printf("%lld\n",ans.a[1][0]-1);
    }
    return 0;
}
