#include "bits/stdc++.h"
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
struct dsu {
    vector<int> parent, group;
 
    dsu(int n) {
        parent = vector<int>(n + 1);
        iota(parent.begin(), parent.end(), 0);
        group = vector<int>(n + 1, 1);
    }
 
    int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = find(parent[i]);
    }
 
    bool samegroup(int x, int y) {
        return find(x) == find(y);
    }
 
    bool merge(int x, int y) {
        int leader1 = find(x);
        int leader2 = find(y);
        if (leader1 == leader2) return 0;
        if (group[leader1] > group[leader2]) swap(leader1, leader2);
        group[leader2] += group[leader1];
        parent[leader1] = leader2;
        return 1;
    }
 
    int getsize(int x) {
        return group[find(x)];
    }
};
 
void work() {
    int n, m, ls = -1;
    cin >> n >> m;
    vector<int> adj[n + 2];
    bool ok = 0;
    dsu ds(n + 2);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if (ok) continue;
        adj[u].push_back(v), adj[v].push_back(u);
        if (ds.merge(u, v)) continue;
        ok = 1;
        ls = v;
    }
    if (!ok) {
        cout << "IMPOSSIBLE" << el;
        return;
    }
    vector<int> vis(n + 1, 0), par(n + 1, -1);
    int aft = 0;
    function<void(int, int)> dfs = [&](int node, int parent) {
        vis[node] = 1;
        par[node] = parent;
        for (auto i: adj[node]) {
            if (i == parent) continue;
            if (!vis[i]) dfs(i, node);
            else if (vis[i] == 1) {
                aft = node;
                break;
            }
        }
        vis[node] = 2;
    };
    dfs(ls, -1);
    vector<int> ans = {ls};
    while (aft != ls) {
        ans.push_back(aft);
        aft = par[aft];
    }
    ans.push_back(ls);
    cout<<ans.size()<<el;
    for (auto i: ans) cout << i << ' ';
}
 
int32_t main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\TEST\\input.txt", "r", stdin);
    freopen("D:\\TEST\\output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
//    cin >> t;
    while (t--) {
        work();
    }
}
