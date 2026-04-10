#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
void work() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 4);
    for (int i = 2, u, v; i <= n; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    vector<vector<int>> dp(n + 2, vector<int>(3, 0));
 
    function<void(int, int)> dfs0 = [&](int u, int p) {
        int sum = 0;
        for (auto v: adj[u]) {
            if (v == p) continue;
            dfs0(v, u);
            sum += dp[v][0];
        }
        dp[u][1] = dp[u][0] = sum;
        for (auto v: adj[u]) {
            if (v == p) continue;
            dp[u][0] = max(dp[u][0], 1 + dp[v][1] + sum - dp[v][0]);
        }
    };
    dfs0(1, 1);
    cout << dp[1][0] << el;
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
