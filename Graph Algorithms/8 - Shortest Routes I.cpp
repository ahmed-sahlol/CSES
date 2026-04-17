#include "bits/stdc++.h"
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
const int N = 2e5 + 5, oo = 1e18;
 
vector<pair<int, int>> adj[N];
 
int dist[N];
 
int parent[N];
 
int n, m;
 
void clear() {
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
    }
}
 
void dijkstra(int src) {
    for (int i = 1; i <= n; ++i) dist[i] = oo;
    dist[src] = 0;
    parent[src] = -1;
 
    priority_queue<pair<int, int>> pq;
    pq.push({0, src});
 
    while (!pq.empty()) {
        int u = pq.top().second;
        int cost = -pq.top().first;
        pq.pop();
 
        if (dist[u] < cost) continue;
 
        for (auto [v, w]: adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({-dist[v], v});
            }
        }
    }
}
 
void work() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c});
    }
    dijkstra(1);
    for (int i = 1; i <= n; i++)cout << dist[i] << ' ';
}
 
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
//    cin >> t;
    while (t--) {
        work();
    }
}
