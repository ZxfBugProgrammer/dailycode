//ø¥¥ÌÃ‚¡À Õ¸¡Àµ»∫≈  ≤¡≤¡≤¡≤¡≤¡≤¡£°£°£°£°£°£°£°£°£°£°
//CodeForces - 321B 
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
const int MAXN = 1000;
const int MAXM = 200 * 200 * 2 + 100;

struct Edge {
    int to, nexte, w, c;
} edge[MAXM];
int cnt, head[MAXN], a[MAXN], b[MAXN], p[MAXN];
int s, t, d[MAXN], v[MAXN], incf[MAXN], pre[MAXN], maxflow, ans;

void Init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
    maxflow = ans = 0;
}

void AddEdge(int from, int to, int c, int w) {
    edge[cnt].to = to;
    edge[cnt].nexte = head[from];
    edge[cnt].c = c;
    edge[cnt].w = w;
    head[from] = cnt++;
}

bool SPFA() {
    queue<int> q;
    memset(d, 0xcf, sizeof(d));
    memset(v, 0, sizeof(v));
    q.push(s);
    d[s] = 0;
    v[s] = 1;
    incf[s] = 1 << 30;
    while (q.size()) {
        int x = q.front();
        v[x] = 0;
        q.pop();
        for (int i = head[x]; i != -1; i = edge[i].nexte) {
            if (!edge[i].c)
                continue;
            int y = edge[i].to;
            if (d[y] < d[x] + edge[i].w) {
                d[y] = d[x] + edge[i].w;
                incf[y] = min(incf[x], edge[i].c);
                pre[y] = i;
                if (!v[y])
                    v[y] = 1, q.push(y);
            }
        }
    }
    return d[t] != 0xcfcfcfcf;
}

void Update() {
    int x = t;
    while (x != s) {
        int i = pre[x];
        edge[i].c -= incf[t];
        edge[i ^ 1].c += incf[t];
        x = edge[i ^ 1].to;
    }
    maxflow += incf[t];
    ans += d[t] * incf[t];
}

int main() {
    int n, m;
    string temp;
    cin >> n >> m;
    Init();
    s = 0, t = n + m + 1;
    for (int i = 1; i <= n; i++) {
        cin >> temp >> a[i];
        p[i] = temp == "ATK" ? 1 : 0;
    }
    for (int i = 1; i <= m; i++)
        cin >> b[i];
    int CGX = 0;
    for (int i = 1; i <= m; i++) {
        AddEdge(s, i, 1, 0);
        AddEdge(i, s, 0, 0);
    }
    for (int i = 1; i <= n; i++) {
        AddEdge(m + i, t, 1, 0);
        AddEdge(t, m + i, 0, 0);
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[j] && b[i] >= a[j]) {
                AddEdge(i, m + j, 1, b[i] - a[j]);
                AddEdge(m + j, i, 0, -(b[i] - a[j]));
            }
        }
    }
    while (SPFA()) {
        if (d[t] < 0)
            break;
        Update();
    }
    CGX = ans;
    if (m > n) {
        Init();
        s = 0, t = n + m + 2;
        for (int i = 1; i <= m; i++) {
            AddEdge(s, i, 1, 0);
            AddEdge(i, s, 0, 0);

            AddEdge(i, n + m + 1, 1, b[i]);
            AddEdge(n + m + 1, i, 0, -b[i]);
        }
        for (int i = 1; i <= n; i++) {
            AddEdge(m + i, t, 1, 0);
            AddEdge(t, m + i, 0, 0);
        }
        AddEdge(m + n + 1, t, m - n, 0);
        AddEdge(t, m + n + 1, 0, 0);

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j] && b[i] >= a[j]) {
                    AddEdge(i, m + j, 1, b[i] - a[j]);
                    AddEdge(m + j, i, 0, -(b[i] - a[j]));
                } else if (!p[j] && b[i] > a[j]) {
                    AddEdge(i, m + j, 1, 0);
                    AddEdge(m + j, i, 0, 0);
                }
            }
        }
        while (SPFA())
            Update();
        if (maxflow == m)
            CGX = max(CGX, ans);
    }
    cout << CGX << endl;
    return 0;
}
