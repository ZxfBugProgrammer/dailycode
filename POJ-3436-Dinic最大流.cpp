#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
const int MAXN = 100, MAXM = 100 * 100, MAXP = 10 + 10, INF = 0x3f3f3f3f;
struct Edge {
    int to, nexte, c;
} edge[MAXM];
int head[MAXN], cnt;
int s, t, maxflow, d[MAXN];
struct Node {
    int q, s[MAXP], d[MAXN];
} a[MAXN];

void Init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
    maxflow = 0;
}

void AddEdge(int from, int to, int c) {
    edge[cnt].to = to, edge[cnt].c = c, edge[cnt].nexte = head[from], head[from] = cnt++;
    edge[cnt].to = from, edge[cnt].c = 0, edge[cnt].nexte = head[to], head[to] = cnt++;
}

bool BFS() {
    memset(d, 0, sizeof(d));
    queue<int> q;
    q.push(s);
    d[s] = 1;
    while (q.size()) {
        int x = q.front();
        q.pop();
        for (int i = head[x]; i != -1; i = edge[i].nexte) {
            if (edge[i].c && !d[edge[i].to]) {
                q.push(edge[i].to);
                d[edge[i].to] = d[x] + 1;
                if (edge[i].to == t) {
                    return true;
                }
            }
        }
    }
    return false;
}

int dinic(int x, int flow) {
    if (x == t)
        return flow;
    int rest = flow, k;
    for (int i = head[x]; i != -1; i = edge[i].nexte) {
        if (edge[i].c && d[edge[i].to] == d[x] + 1) {
            k = dinic(edge[i].to, min(rest, edge[i].c));
            if (!k)
                d[edge[i].to] = 0;
            edge[i].c -= k;
            edge[i ^ 1].c += k;
            rest -= k;
        }
    }
    return flow - rest;
}

int GetMaxflow() {
    int flow = 0;
    while (BFS())
        while ((flow = dinic(s, INF)) != 0)
            maxflow += flow;
    return maxflow;
}

int main() {
    int n, p;
    while (scanf("%d %d", &p, &n) != EOF) {
        Init();
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i].q);
            for (int j = 0; j < p; j++)
                scanf("%d", &a[i].s[j]);
            for (int j = 0; j < p; j++)
                scanf("%d", &a[i].d[j]);
        }
        s = n + n, t = n + n + 1;
        for (int i = 0; i < n; i++) {
            AddEdge(i, n + i, a[i].q);
            int nums = 0, numd = 0;
            for (int j = 0; j < p; j++) {
                if (a[i].s[j] == 1)
                    nums++;
                if (a[i].d[j] == 1)
                    numd++;
            }
            if (nums == 0)
                AddEdge(s, i, INF);
            if (numd == p)
                AddEdge(n + i, t, INF);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                bool flag = true;
                for (int k = 0; k < p; k++) {
                    if ((a[i].d[k] ^ a[j].s[k]) == 1) { // 一定要注意位运算的优先级！！！！！！！！！！
                        flag = false;
                        break;
                    }
                }
                if (flag)
                    AddEdge(n + i, j, INF);
            }
        }
        printf("%d ", GetMaxflow());
        int num = 0;
        for (int i = 0; i < n; i++) {
            for (int k = head[n + i]; k != -1; k = edge[k].nexte) {
                int to = edge[k].to;
                if (to != i && to != s && to != t && edge[k].c != INF) {
                    num++;
                }
            }
        }
        printf("%d\n", num);
        for (int i = 0; i < n; i++) {
            for (int k = head[n + i]; k != -1; k = edge[k].nexte) {
                int to = edge[k].to;
                if (to != i && to != s && to != t && edge[k].c != INF) {
                    printf("%d %d %d\n", i + 1, to + 1, INF - edge[k].c);
                }
            }
        }
    }
    return 0;
}
