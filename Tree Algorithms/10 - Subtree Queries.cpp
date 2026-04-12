#include "bits/stdc++.h"
 
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
 
const int N=2e5+5;
 
vector<vector<int>> adj(N);
 
vector<int> arr(N), IN(N), OUT(N);
 
int timer = 0;
 
void dfs0(int u,int p) {
    IN[u] = timer++;
    for (auto v: adj[u]) {
        if (v == p) continue;
        dfs0(v, u);
    }
    OUT[u] = timer - 1;
}
 
void work() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    for (int i = 2, u, v; i <= n; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs0(1, 1);
    sagara seg(n);
    for (int i = 1; i <= n; i++) {
        seg.set(IN[i], arr[i]);
    }
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int u, val;
            cin >> u >> val;
            seg.set(IN[u], val);
        } else {
            int u;
            cin >> u;
            cout << seg.query(IN[u], OUT[u] + 1).val << el;
        }
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
