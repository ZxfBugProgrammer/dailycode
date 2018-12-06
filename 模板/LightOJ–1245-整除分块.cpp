#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;
typedef long long ll;

int main() {
    int T,cas=1;
    scanf("%d", &T);
    while (T--) {
        ll n, ans = 0;
        scanf("%lld", &n);
        for (ll l = 1, r; l <= n; l = r + 1) {
            r = n / (n / l);
            ans += (r - l + 1) * (n / l);
        }
        printf("Case %d: %lld\n",cas++,ans);
    }
    return 0;
}

