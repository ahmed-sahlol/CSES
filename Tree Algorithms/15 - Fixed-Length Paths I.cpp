#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
int n, k;
// Original Tree
vector<vector<int>> adj;
vector<bool> deleted;
vector<int> sz;
int tot, ans;
 
// Centroid Tree
vector<int> par, lvl;
vector<int> dist;
 
// Calculate the size of each subtree
void dfs0(int u, int p) {
    sz[u] = 1;
    ++tot;
    for (auto v: adj[u]) {
        if (v == p || deleted[v]) continue;
        dfs0(v, u);
        sz[u] += sz[v];
    }
}
 
int find_centroid(int u, int p) {
    for (auto v: adj[u]) {
        if (deleted[v] || v == p || sz[v] <= tot / 2) continue;
        return find_centroid(v, u);
    }
    return u;
}
 
void add_edge(int u, int p) { par[u] = p, lvl[u] = lvl[p] + 1; }
 
void dfs(int u, int p, int d) {
    if (d > k) return;
//    cout << u << ' ' << d << ' ' << k - d << ' ' << dist[k - d] << el;
    ans += dist[k - d];
    for (auto v: adj[u]) {
        if (v == p || deleted[v]) continue;
        dfs(v, u, d + 1);
    }
}
 
void add(int u, int p, int d) {
    if (d > k) return;
    dist[d]++;
    for (auto v: adj[u]) {
        if (v == p || deleted[v]) continue;
        add(v, u, d + 1);
    }
}
 
void solve(int u, int p = -1) {
    tot = 0;
    dfs0(u, p);
    int curr_centroid = find_centroid(u, u);
    if (p == -1) p = curr_centroid;
    add_edge(curr_centroid, p);
    lvl[curr_centroid] = 0;
    dist[0] = 1;
    // The process part to calculate the desired property
    for (auto v: adj[curr_centroid]) {
        if (deleted[v] || v == p) continue;
        dfs(v, curr_centroid, lvl[curr_centroid] + 1);
        add(v, curr_centroid, lvl[curr_centroid] + 1);
    }
    // Delete the current_centroid from the tree and search for the remainings
    for (int i = 0; i <= sz[curr_centroid]; ++i) dist[i] = 0;
    deleted[curr_centroid] = 1;
    for (auto &v: adj[curr_centroid]) {
        if (deleted[v]) continue;
        solve(v, curr_centroid);
    }
}
 
void init() {
    tot = ans = 0;
    adj.assign(n + 1, {});
    deleted.assign(n + 1, 0);
    sz.assign(n + 1, 0);
    par.assign(n + 1, 0);
    lvl.assign(n + 1, 0);
    dist.assign(n + 1, 0);
}
 
void work() {
    cin >> n >> k;
    init();
    for (int i = 2, u, v; i <= n; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    solve(1);
    cout << ans << el;
}
 
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int tc = 1;
//    cin >> tc;
    for (int T = 1; T <= tc; ++T) {
//        cout << "Case " << T << ": ";
        work();
    }
}
