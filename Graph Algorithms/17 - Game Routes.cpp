#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
const int mod = 1e9 + 7;
 
void work() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 5);
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
    }
    vector<int> dp(n + 2, -1);
    function<int(int)> dfs0 = [&](int u) -> int {
        if (u == n) return 1;
        int &ret = dp[u];
        if (~ret) return ret;
        ret = 0;
        for (auto v: adj[u]) {
            ret += dfs0(v);
            ret %= mod;
        }
        return ret;
    };
 
    cout << dfs0(1) << el;
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
