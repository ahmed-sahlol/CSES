#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
void work() {
    int n, m;
    cin >> n >> m;
    vector <vector<int>> adj(n + 2);
    vector<int> in(n + 4), res;
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        in[v]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; ++i)if (in[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        res.emplace_back(u);
        for (int v: adj[u])
            if (!--in[v])q.push(v);
    }
    if (res.size() != n) return void(cout << "IMPOSSIBLE" << el);
    for (auto i: res) cout << i << ' ';
    cout << el;
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
