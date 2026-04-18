#include <bits/stdc++.h>
using namespace std;
 
#define int long long
const long long INF = 1e18;
 
struct Edge {
    int u, v, w;
};
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, m;
    cin >> n >> m;
 
    vector<Edge> edges;
    vector<vector<int>> adj(n + 1);
 
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, -w});
        adj[u].push_back(v);
    }
 
    vector<long long> dist(n + 1, INF);
    dist[1] = 0;
 
    // Bellman-Ford
    for (int i = 1; i <= n - 1; i++) {
        for (auto &e : edges) {
            if (dist[e.u] < INF) {
                dist[e.v] = min(dist[e.v], dist[e.u] + e.w);
            }
        }
    }
 
    vector<bool> inNeg(n + 1, false);
    for (auto &e : edges) {
        if (dist[e.u] < INF && dist[e.v] > dist[e.u] + e.w) {
            inNeg[e.v] = true;
        }
    }
 
    queue<int> q;
    vector<bool> vis(n + 1, false);
 
    for (int i = 1; i <= n; i++) {
        if (inNeg[i]) {
            q.push(i);
            vis[i] = true;
        }
    }
 
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
 
    if (vis[n]) {
        cout << -1 << '\n';
    } else {
        cout << -dist[n] << '\n';
    }
 
    return 0;
}
