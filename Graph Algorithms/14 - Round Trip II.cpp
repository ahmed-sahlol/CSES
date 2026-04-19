#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
struct SCC {
    int N, M;
    vector<vector<int>> adj, rev_adj, comp;
    vector<int> out, curr_path, roots;
    vector<bool> vis;
 
    SCC(int n, vector<vector<int>> graph) {
        N = n;
        adj = graph;
        rev_adj.assign(N + 5, {});
        vis.assign(N + 5, 0);
        roots.assign(N + 5, 0);
        for (int i = 1; i <= n; ++i)
            for (auto v: adj[i])
                rev_adj[v].push_back(i);
        scc();
    }
 
    void dfs0(int u) {
        vis[u] = 1;
        for (auto v: adj[u])
            if (!vis[v]) dfs0(v);
        out.push_back(u);
    }
 
    void dfs1(int u) {
        vis[u] = 1;
        for (auto v: rev_adj[u])
            if (!vis[v]) dfs1(v);
        curr_path.push_back(u);
    }
 
    void scc() {
        for (int i = 1; i <= N; ++i) if (!vis[i]) dfs0(i);
 
        vis.assign(N + 5, 0);
        reverse(out.begin(), out.end());
 
        for (auto v: out) {
            if (vis[v]) continue;
            dfs1(v);
            comp.push_back(curr_path);
            int root = *min_element(curr_path.begin(), curr_path.end());
            for (auto u: curr_path) roots[u] = root;
            curr_path.clear();
        }
    }
};
 
void work() {
    int n, m;
    cin >> n >> m;
 
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
 
    SCC scc(n, adj);
 
    vector<int> all;
 
    for (auto &c: scc.comp) {
        if (c.size() > 1) {
            all = c;
            break;
        }
        int u = c[0];
        for (auto v: adj[u]) {
            if (v == u) {
                all = c;
                break;
            }
        }
        if (!all.empty()) break;
    }
 
    if (all.empty()) {
        cout << "IMPOSSIBLE\n";
        return;
    }
 
    vector<bool> in_scc(n + 1, false);
    for (auto u: all) in_scc[u] = true;
 
    vector<int> state(n + 1, 0), parent(n + 1, -1);
    vector<int> cycle;
 
    function<bool(int)> dfs = [&](int u) {
        state[u] = 1;
        for (auto v: adj[u]) {
            if (!in_scc[v]) continue;
 
            if (state[v] == 0) {
                parent[v] = u;
                if (dfs(v)) return true;
            } else if (state[v] == 1) {
                cycle.push_back(v);
                int cur = u;
                while (cur != v) {
                    cycle.push_back(cur);
                    cur = parent[cur];
                }
                cycle.push_back(v);
                reverse(cycle.begin(), cycle.end());
                return true;
            }
        }
        state[u] = 2;
        return false;
    };
 
    dfs(all[0]);
 
    cout << cycle.size() << "\n";
    for (auto x: cycle) cout << x << " ";
    cout << "\n";
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
