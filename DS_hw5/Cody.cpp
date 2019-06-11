#include <iostream>
#include <queue>
#include <vector>
#define INF 1000000000
using namespace std;
using pii = pair<int, int>;

struct edge {
    int dst, l, b;
};

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<edge>> g(m);
    for (int i = 0; i < n; i++) {
        int w, x, y, z;
        cin >> w >> x >> y >> z;
        g[w].push_back({x, y, z});
    }

    vector<int> d(m, INF);
    d[0] = 0;
    priority_queue<pii> pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto tmp = pq.top();
        pq.pop();
        int u = tmp.second;
        if (tmp.first != d[u]) continue;
        for (int i = 0; i < g[u].size(); i++) {
            edge &e = g[u][i];
            if (d[e.dst] > d[u] + e.l) {
                d[e.dst] = d[u] + e.l;
                pq.push(make_pair(d[e.dst], e.dst));
            }
        }
    }

    vector<int> b(m, 0);
    b[0] = INF;
    priority_queue<pii, vector<pii>, greater<pii>> pq2;
    pq2.push({INF, 0});
    while (!pq2.empty()) {
        auto tmp = pq2.top();
        pq2.pop();
        int u = tmp.second;
        if (tmp.first != b[u]) continue;
        for (int i = 0; i < g[u].size(); i++) {
            edge &e = g[u][i];
            if (b[e.dst] < min(b[u], e.b)) {
                b[e.dst] = min(b[u], e.b);
                pq2.push(make_pair(b[e.dst], e.dst));
            }
        }
    }

    for (int i = 1; i < m; i++) {
        cout << i << ' ';
        d[i] == INF ? cout << "inf" : cout << d[i];
        cout << ' ' << b[i] << endl;
    }
}
