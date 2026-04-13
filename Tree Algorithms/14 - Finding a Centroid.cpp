#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
const int N = 2e5 + 5;
vector<int> adj[N];
int sz[N], tot = 0;
 
void dfs0(int u, int p) {
    ++tot;
    sz[u] = 1;
    for (auto v: adj[u]) {
        if (v == p) continue;
        dfs0(v, u);
        sz[u] += sz[v];
    }
}
 
int get_centroid(int u, int p) {
    for (auto v: adj[u]) {
        if (v == p) continue;
        if (sz[v] > tot / 2) return get_centroid(v, u);
    }
    return u;
}
 
void decompse(int u, int p) {
    dfs0(1, 1);
    cout << get_centroid(1, 1) << el;
}
 
void work() {
    int n;
    cin >> n;
 
    for (int i = 2, u, v; i <= n; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    decompse(1, 1);
}
 
int32_t main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int tc = 1;
//    cin >> tc;
    for (int T = 1; T <= tc; ++T) {
//        cout << "Case " << T << ": ";
        work();
    }
}
