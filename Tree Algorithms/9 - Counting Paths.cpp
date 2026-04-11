#include "bits/stdc++.h"
 
//#define int long long
 
#define el '\n'
 
using namespace std;
 
vector<vector<int>> adj;
 
vector<int> lvl;
 
vector<vector<int>>up;
 
int LOG;
 
void dfs0(int u, int p = 0) {
    for (int i = 1; i < LOG; i++) {
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for (auto v: adj[u]) {
        if (v == p)continue;
        up[0][v] = u;
        lvl[v] = lvl[u] + 1;
        dfs0(v, u);
    }
}
 
int LCA(int u, int v) {
    if (lvl[u] < lvl[v]) {
        swap(u, v);
    }
    int diff = lvl[u] - lvl[v];
    for (int i = 0; diff; diff >>= 1, ++i) {
        if (diff & 1) {
            u = up[i][u];
        }
    }
    if (u == v)return u;
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[i][u] != up[i][v]) {
            u = up[i][u], v = up[i][v];
        }
    }
    return up[0][u];
}
 
void compute(int root = 1) {
    LOG = __lg(adj.size()) + 1;
    lvl.assign(adj.size(), {});
    up.assign(LOG, vector<int>(adj.size()));
    dfs0(root);
}
 
void work() {
    int n, q;
    cin >> n >> q;
    adj.assign(n + 5, {});
    vector<pair<int, int>> vv;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    compute(1);
    vector<int> pre(n + 4, 0);
    map<pair<int, int>, int> mx;
    while (q--) {
        int u, v;
        cin >> u >> v;
        int lca = LCA(u, v);
        pre[lca]--;
        if (up[0][lca] != 0) pre[up[0][lca]]--;
        pre[u]++;
        pre[v]++;
    }
    function<void(int, int)> dfs = [&](int u, int p) {
        for (auto v: adj[u]) {
            if (v == p) continue;
            dfs(v, u);
            pre[u] += pre[v];
        }
    };
    dfs(1, 1);
    for (int i = 1; i <= n; i++) cout << pre[i] << ' ';
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
