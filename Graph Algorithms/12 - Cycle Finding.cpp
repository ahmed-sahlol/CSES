#include <bits/stdc++.h>
using namespace std;
 
#define int long long
const int INF = 1e18;
 
struct Edge {
    int u, v, w;
};
 
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, m;
    cin >> n >> m;
 
    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
 
    vector<int> dist(n + 1, 0);
    vector<int> parent(n + 1, -1);
 
    int last = -1;
 
    // Bellman-Ford
    for (int i = 1; i <= n; i++) {
        last = -1;
        for (auto &e : edges) {
            if (dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;
                parent[e.v] = e.u;
                last = e.v;
            }
        }
    }
 
    if (last == -1) {
        cout << "NO\n";
        return 0;
    }
 
    // ندخل جوه cycle
    for (int i = 0; i < n; i++)
        last = parent[last];
 
    // نطلع cycle
    vector<int> cycle;
    int cur = last;
 
    do {
        cycle.push_back(cur);
        cur = parent[cur];
    } while (cur != last);
 
    cycle.push_back(last);
    reverse(cycle.begin(), cycle.end());
 
    cout << "YES\n";
    for (auto x : cycle) cout << x << " ";
    cout << '\n';
 
    return 0;
}
