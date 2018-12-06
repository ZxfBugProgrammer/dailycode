//不想写了 粘题解 这题很简单 wa那一次是因为想当然了
#include <math.h>
#include <vector>
#include <queue>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
typedef long long LL;
 
LL solve(LL n)
{
    LL num=0;
    while(n){
        num+=n/5;
        n/=5;
    }
    return num;
}
 
LL er(LL n)
{
    LL x=1;
    LL y=1844674407370;
    LL mid;
    LL res=-1;
    while(y>=x){
        mid=(x+y)/2;
        LL ans=solve(mid);
        if(ans==n){
            res=mid;
            y=mid-1;
            //return mid;
        }
        else if(ans>n){
            y=mid-1;
        }
        else if(ans<n){
            x=mid+1;
        }
    }
    return res;
}
int main()
{
 
    int t;
    scanf("%d",&t);
    int xp=1;
    while(t--){
        LL n;
        scanf("%lld",&n);
        LL ans=er(n);
        if(ans==-1)  printf("Case %d: impossible\n",xp++);
        else printf("Case %d: %d\n",xp++,ans);
    }
    return 0;
}


