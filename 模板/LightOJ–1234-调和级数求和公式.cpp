//¹«Ê½
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const double ER = 0.57721566490153286060651209;
double fn[100005];

void Init() {
    fn[0] = 0, fn[1] = 1;
    for (int i = 2; i <= 100000; i++)
        fn[i] = fn[i - 1] + 1.0 / i;
}

double find(int n) {
    return ER + (log(n) + log(n + 1)) / 2;
}

int main() {
    Init();
    int T, cas = 1;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        printf("Case %d: ", cas++);
        if (n <= 100000)
            printf("%.10lf\n", fn[n]);
        else
            printf("%.10lf\n", find(n));
    }
    return 0;
}

