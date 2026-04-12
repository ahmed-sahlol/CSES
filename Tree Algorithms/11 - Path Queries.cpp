#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
struct Node {
    int val;
 
    Node() {
        val = 0;
    }
 
    Node(int x) {
        val = x;
    }
 
    void change(int x) {
        val = x;
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
 
    Node query(int l, int r) {
        return query(l, r, 0, 0, tree_size);
    }
 
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
 
    void set(int idx, int val) {
        set(idx, val, 0, 0, tree_size);
    }
 
};
 
int n, q, Log, timer;
vector<vector<int>> adj;
vector<vector<int>> up;
vector<int> val, in, out, lvl;
 
void dfs0(int u,int p) {
    in[u] = timer++;
    for (int i = 1; i < Log; ++i) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (auto v: adj[u]) {
        if (v == p) continue;
        up[v][0] = u;
        lvl[v] = lvl[u] + 1;
        dfs0(v, u);
    }
    out[u] = timer++;
}
 
int LCA(int u,int v) {
    if (lvl[v] > lvl[u]) swap(u, v);
    int diff = lvl[u] - lvl[v];
    for (int i = 0; diff; diff >>= 1, ++i) {
        if (diff & 1) {
            u = up[u][i];
        }
    }
    if (u == v) return u;
    for (int i = Log; i >= 0; --i) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}
 
void work() {
    cin >> n >> q;
    Log = __lg(n) + 1;
    adj.assign(n + 5, {});
    up.assign(n + 5, vector<int>(Log + 5, 0));
    in = out = lvl = val = vector<int>(n + 5, 0);
    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 2, u, v; i <= n; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs0(1, 0);
    sagara seg(timer);
    for (int i = 1; i <= n; ++i) {
        seg.set(in[i], val[i]);
        seg.set(out[i], -val[i]);
    }
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, value;
            cin >> u >> value;
            seg.set(in[u], value);
            seg.set(out[u], -value);
        } else {
            int u = 1, v;
            cin >> v;
            cout << seg.query(in[u], in[v] + 1).val << el;
        }
    }
}
