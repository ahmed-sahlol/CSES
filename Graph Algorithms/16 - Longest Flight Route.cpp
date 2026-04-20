#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
void work() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 4);
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
    }
 
    vector<int> dp(n + 3, -1), nxt(n + 2, -1);
    function<int(int)> dfs0 = [&](int u) -> int {
        if (u == n) return dp[n] = 1;
        if (~dp[u]) return dp[u];
        dp[u] = 0;
        for (auto v: adj[u]) {
            dfs0(v);
            if (dp[v] && dp[u] < dp[v] + 1) {
                dp[u] = dp[v] + 1;
                nxt[u] = v;
            }
        }
        return dp[u];
    };
    dfs0(1);
    if (dp[n] == -1) return void(cout << "IMPOSSIBLE" << el);
    cout << dp[1] << el;
    for (int u = 1; ~nxt[u]; u = nxt[u]) cout << u << ' ';
    cout << n << el;
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
