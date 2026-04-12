#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
 
int n;
vector<int> val, res;
vector<vector<int>> adj;
vector<set<int>> col;
 
void dfs0(int u, int p) {
    col[u].insert(val[u]);
    for (auto v: adj[u]) {
        if (v == p) continue;
        dfs0(v, u);
        if (col[u].size() < col[v].size()) swap(col[u], col[v]);
        for (auto i: col[v]) col[u].insert(i);
    }
    res[u] = col[u].size();
}
 
void work() {
    cin >> n;
 
    val.assign(n + 1, 0);
    res.assign(n + 1, 0);
    adj.assign(n + 5, {});
    col.assign(n + 5, {});
 
    for (int i = 1; i <= n; ++i) cin >> val[i];
 
    for (int i = 2, u, v; i <= n; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    dfs0(1, 1);
 
    for (int i = 1; i <= n; ++i) cout << res[i] << ' ';
}
 
int32_t main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\test\\input.txt", "r", stdin);
    freopen("D:\\test\\output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int tc = 1;
//    cin >> tc;
    for (int T = 1; T <= tc; ++T) {
//        cout << "Case " << T << ":" << el;
        work();
    }
}
