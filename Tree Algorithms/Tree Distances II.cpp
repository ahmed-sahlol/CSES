#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
void work() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 5);
    for (int i = 2, u, v; i <= n; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> sum(n + 3, 0), dp(n + 3, 0), redp(n + 3, 0);
    function<void(int, int)> dfs0 = [&](int u, int p) {
        dp[u] = 0;
        sum[u] = 1;
        for (auto v: adj[u]) {
            if (v == p) continue;
            dfs0(v, u);
            sum[u] += sum[v];
            dp[u] += (dp[v] + sum[v]);
        }
    };
 
    function<int(int, int)> reroot = [&](int u, int p) -> int {
        int ans = dp[u];
        redp[u] = dp[u];
        for (auto v: adj[u]) {
            if (v == p) continue;
 
            sum[u] -= sum[v];
            dp[u] -= dp[v] + sum[v];
            sum[v] += sum[u];
            dp[v] += dp[u] + sum[u];
 
            redp[v] = dp[v];
 
            ans = max(ans, reroot(v, u));
 
            dp[v] -= sum[u] + dp[u];
            sum[v] -= sum[u];
            dp[u] += dp[v] + sum[v];
            sum[u] += sum[v];
        }
        return ans;
    };
 
    dfs0(1, -1);
    reroot(1, -1);
    for (int i = 1; i <= n; ++i) cout << redp[i] << ' ';
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
