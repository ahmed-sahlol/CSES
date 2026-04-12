#include <bits/stdc++.h>
 
//#define int long long
 
#define el '\n'
 
using namespace std;
 
struct Node {
    int val;
 
    Node() {
        val = INT32_MIN;
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
        ans.val = max(lf.val, ri.val);
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
 
    void init(vector<int> &arr, int ni, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < arr.size())segdata[ni] = Node(arr[lx]);
            return;
        }
        int mid = (rx + lx) >> 1;
        init(arr, 2 * ni + 1, lx, mid);
        init(arr, 2 * ni + 2, mid, rx);
        segdata[ni] = merge(segdata[2 * ni + 1], segdata[2 * ni + 2]);
    }
 
    void init(vector<int> &arr) {
        init(arr, 0, 0, tree_size);
    }
 
};
 
const int N = 2e5 + 5;
 
vector<int> adj[N];
 
int n, q, timer, in[N], val[N], sz[N], big[N], head[N], par[N], lvl[N];
 
void dfs0(int u, int p) {
    sz[u] = 1;
    for (auto v: adj[u]) {
        if (v == p) continue;
        par[v] = u;
        lvl[v] = lvl[u] + 1;
        dfs0(v, u);
        sz[u] += sz[v];
        if (big[u] == 0 || sz[v] > sz[big[u]]) {
            big[u] = v;
        }
    }
}
 
void flatin(int u, int p) {
    in[u] = timer++;
 
    // heavy edge
    if (big[u] != 0) {
        head[big[u]] = head[u];
        flatin(big[u], u);
    }
 
    // light edge
    for (auto v: adj[u]) {
        if (v == p || v == big[u]) continue;
        head[v] = v;
        flatin(v, u);
    }
}
 
vector<pair<int, int>> HLD(int u, int v) {
    vector<pair<int, int>> res;
    while (true) {
        if (head[u] == head[v]) {
            if (lvl[u] < lvl[v]) swap(u, v);
            res.push_back(make_pair(in[v], in[u]));
            return res;
        }
        if (lvl[head[v]] > lvl[head[u]]) swap(u, v);
        res.push_back(make_pair(in[head[u]], in[u]));
        u = par[head[u]];
    }
    return res;
}
 
void init(int root = 1) {
    lvl[root] = 1;
    par[root] = root;
    head[root] = root;
    timer = 0;
    dfs0(root, -1);
    flatin(root, -1);
}
 
void work() {
    cin >> n >> q;
 
    for (int i = 1; i <= n; ++i) cin >> val[i];
 
    for (int i = 2, u, v; i <= n; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    init(1);
 
    sagara seg(n);
    vector<int> arr(n);
    for (int i = 1; i <= n; ++i) arr[in[i]] = val[i];
    seg.init(arr);
 
    int type, u, v;
    while (q--) {
        cin >> type >> u >> v;
        if (type == 1) seg.set(in[u], v);
        else {
            vector<pair<int, int>> segs = HLD(u, v);
            int ans = INT32_MIN;
            for (auto [a, b]: segs)ans = max(ans, seg.query(a, b + 1).val);
            cout << ans << ' ';
        }
    }
}
 
int32_t main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\test\\input.txt", "r", stdin);
    freopen("D:\\test\\output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tc = 1;
//    cin >> tc;
    for (int T = 1; T <= tc; ++T) {
//        cout << "Case " << T << ":" << el;
        work();
    }
}
