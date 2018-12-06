#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <string>
#include <map>

using namespace std;

const int MAXN = 300 + 100, MAXM = 300 * 300 + 100;
struct Edge {
    int to, nexte, c;
} edge[MAXM];
int head[MAXN], cnt;
int s, t, d[MAXN];
string a[100 + 10], b[100 + 10];
pair<string, string> c[MAXN];

void Init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
}

void AddEdge(int from, int to, int c) {
    edge[cnt].to = to;
    edge[cnt].c = c;
    edge[cnt].nexte = head[from];
    head[from] = cnt++;
    edge[cnt].to = from;
    edge[cnt].c = 0;
    edge[cnt].nexte = head[to];
    head[to] = cnt++;
}

bool BFS() {
    memset(d, 0, sizeof(d));
    queue<int> q;
    q.push(s), d[s] = 1;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = head[x]; i != -1; i = edge[i].nexte) {
            if (edge[i].c && !d[edge[i].to]) {
                q.push(edge[i].to);
                d[edge[i].to] = d[x] + 1;
                if (edge[i].to == t)
                    return true;
            }
        }
    }
    return false;
}

int Dinic(int x, int flow) {
    if (x == t)
        return flow;
    int rest = flow, k;
    for (int i = head[x]; i != -1; i = edge[i].nexte) {
        if (edge[i].c && d[edge[i].to] == d[x] + 1) {
            k = Dinic(edge[i].to, min(rest, edge[i].c));
            if (!k)
                d[edge[i].to] = 0;
            edge[i].c -= k;
            edge[i ^ 1].c += k;
            rest -= k;
        }
    }
    return flow - rest;
}

int GetMaxFlow() {
    int flow = 0, maxflow = 0;
    while (BFS()) {
        while ((flow = Dinic(s, 0x3f3f3f3f)) != 0)
            maxflow += flow;
    }
    return maxflow;
}

int main() {
    Init();
    int n1, n2, n3;
    scanf("%d", &n1);
    for (int i = 0; i < n1; i++)
        cin >> a[i];
    scanf("%d", &n2);
    string temp;
    for (int i = 0; i < n2; i++)
        cin >> temp >> b[i];
    scanf("%d", &n3);
    for (int i = 0; i < n3; i++)
        cin >> c[i].first >> c[i].second;
    s = n1 + n2 + n3;
    t = s + 1;
    for (int i = 0; i < n1; i++) {
        AddEdge(i, t, 1);
        for (int j = 0; j < n3; j++)
            if (c[j].second == a[i])
                AddEdge(n1 + n2 + j, i, 1);
    }
    for (int i = 0; i < n2; i++) {
        AddEdge(s, n1 + i, 1);
        for (int j = 0; j < n3; j++)
            if (c[j].first == b[i])
                AddEdge(n1 + i, n1 + n2 + j, 1);
        for (int j = 0; j < n1; j++) {
            if (b[i] == a[j])
                AddEdge(n1 + i, j, 1);
        }
    }
    for (int i = 0; i < n3; i++)
        for (int j = 0; j < n3; j++)
            if (c[i].second == c[j].first)
                AddEdge(n1 + n2 + i, n1 + n2 + j, 1);
    printf("%d\n", n2 - GetMaxFlow());
    return 0;
}
