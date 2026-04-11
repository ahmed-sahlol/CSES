#include "bits/stdc++.h"
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
const int N=2e5+5,Log = 23;
 
vector<vector<int>>up(N,vector<int>(23));
 
vector<int>adj[N];
 
vector<int>lvl(N);
 
void dfs0(int node,int par) {
    lvl[node] = lvl[par] + 1;
    up[node][0] = par;
    for (int i = 1; i < Log; i++) {
        up[node][i] = up[up[node][i - 1]][i - 1];
    }
    for (auto i: adj[node]) {
        if (i != par) {
            dfs0(i, node);
        }
    }
}
 
int Kth(int node,int K) {
    for (int i = Log - 1; i >= 0; --i) {
        if ((K >> i) & 1) {
            node = up[node][i];
        }
    }
    if (node == 0) node = -1;
    return node;
}
 
void work() {
    int n, q;
    cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        int u;
        cin >> u;
        adj[u].push_back(i);
        adj[i].push_back(u);
    }
    dfs0(1, 0);
    while (q--) {
        int u, k;
        cin >> u >> k;
        cout << Kth(u, k) << el;
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
