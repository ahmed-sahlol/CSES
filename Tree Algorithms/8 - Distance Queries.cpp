#include "bits/stdc++.h"
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
 
int LOG ;
 
vector<vector<int>>adj,up;
 
vector<int>lvl;
 
void dfs0(int node,int par) {
    lvl[node] = lvl[par] + 1;
    up[node][0] = par;
    for (int i = 1; i < LOG; i++) {
        up[node][i] = up[up[node][i - 1]][i - 1];
    }
    for (auto i: adj[node]) {
        if (i != par) {
            dfs0(i, node);
        }
    }
}
 
int Kth(int node,int K) {
    for (int i = LOG - 1; i >= 0; --i) {
        if ((K >> i) & 1) {
            node = up[node][i];
        }
    }
    if (node == 0) node = -1;
    return node;
}
 
int LCA(int u,int v) {
    if (lvl[u] < lvl[v]) swap(u, v);
    u = Kth(u, lvl[u] - lvl[v]);
    // same lvl
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i],
                    v = up[v][i];
        }
    }
    return up[v][0];
}
 
int Distance(int u,int v) {
    int lca = LCA(u, v);
    return lvl[u] + lvl[v] - 2 * lvl[lca];
}
 
void work() {
    int n, q;
    cin >> n >> q;
    LOG = __lg(n + 3) + 2;
    adj.assign(n + 5, {});
    up.assign(n + 5, vector<int>(LOG));
    lvl.assign(n + 5, 0);
    set<int> st;
    for (int i = 1; i <= n; i++) st.insert(i);
    for (int i = 2; i <= n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        st.erase(v);
    }
    dfs0(*st.begin(), 0);
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << Distance(u, v) << el;
    }
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
