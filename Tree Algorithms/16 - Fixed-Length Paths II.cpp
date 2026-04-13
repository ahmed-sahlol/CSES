#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
struct Node {
    int val;
 
    Node() {
        val = 0;
    }
 
    void change(int x) {
        val += x;
    }
};
 
struct sagara {
    vector<Node> segdata;
    int tree_size;
 
    sagara(int n) {
        tree_size = 1;
        while (tree_size < n) tree_size *= 2;
        segdata.assign(2 * tree_size, Node());
    }
 
    Node merge(Node &lf, Node &ri) {
        Node ans = Node();
        ans.val = lf.val + ri.val;
        return ans;
    }
 
    Node query(int l, int r, int ni, int lx, int rx) {
        if (l >= rx || lx >= r) return Node();
        if (lx >= l && r >= rx) return segdata[ni];
        int mid = (lx + rx) / 2;
        Node lf = query(l, r, 2 * ni + 1, lx, mid);
        Node ri = query(l, r, 2 * ni + 2, mid, rx);
        return merge(lf, ri);
    }
 
    Node query(int l, int r) { return query(l, r, 0, 0, tree_size); }
 
    void set(int idx, int val, int ni, int lx, int rx) {
        if (rx - lx == 1) {
            segdata[ni].change(val);
            return;
        }
        int mid = (lx + rx) / 2;
        if (idx >= mid) set(idx, val, 2 * ni + 2, mid, rx);
        else set(idx, val, 2 * ni + 1, lx, mid);
        segdata[ni] = merge(segdata[2 * ni + 1], segdata[2 * ni + 2]);
    }
 
    void set(int idx, int val) { set(idx, val, 0, 0, tree_size); }
};
 
const int N = 2e5 + 5;
 
int n, q, k1, k2, ret, timer;
 
sagara seg(N);
 
vector<vector<int>> adj(N);
vector<int> sz(N), big(N), ans(N), lvl(N), in(N), know(N);
 
void dfs0(int u, int p) {
    in[u] = timer;
    know[timer++] = u;
    sz[u] = 1;
    for (auto v: adj[u]) {
        if (v == p) continue;
        lvl[v] = lvl[u] + 1;
        dfs0(v, u);
        sz[u] += sz[v];
        if (big[u] == 0 || sz[v] > sz[big[u]]) {
            big[u] = v;
        }
    }
}
 
void update(int u, int d) { seg.set(lvl[u], d); }
 
void collect(int u, int p, int d) {
    update(u, d);
    for (auto v: adj[u]) {
        if (v == p) continue;
        collect(v, u, d);
    }
}
 
void dfs(int u, int p, bool keep) {
    for (auto v: adj[u]) {
        if (v == p || v == big[u]) continue;
        dfs(v, u, false);
    }
 
    if (big[u] != 0) dfs(big[u], u, true);
 
    // add light node
    for (auto v: adj[u]) {
        if (v == p || v == big[u]) continue;
        int l = in[v], r = in[v] + sz[v];
        for (int i = l; i < r; ++i) {
            int node = know[i];
            int d2 = k1 - lvl[node] + 2 * lvl[u];
            int d3 = k2 - lvl[node] + 2 * lvl[u];
            if (lvl[node] - lvl[u] < k1) {
                ret += seg.query(min(n, d2), min(n, d3) + 1).val;
            } else if (lvl[node] - lvl[u] < k2) {
                ret += seg.query(lvl[u] + 1, min(n, d3) + 1).val;
            }
        }
        collect(v, u, 1);
    }
 
    update(u, 1);
 
    ret += seg.query(min(n, lvl[u] + k1), min(n, lvl[u] + k2) + 1).val;
 
    if (!keep) collect(u, p, -1);
}
 
void work() {
    cin >> n >> k1 >> k2;
 
    for (int i = 2, u, v; i <= n; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    dfs0(1, 1);
    dfs(1, 1, false);
 
    cout << ret << el;
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
