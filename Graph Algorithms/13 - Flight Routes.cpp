#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
void work() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> adj(n + 2);
    for (int i = 1, u, v, w; i <= m; ++i) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    priority_queue<int> tot[n + 2];
    priority_queue<pair<int, int>> pq;
    pq.push({0, 1});
    while (pq.size()) {
        auto [cost, u] = pq.top();
        pq.pop();
        if (tot[u].size() >= k) continue;
        cost *= -1;
        tot[u].push(cost);
        for (auto [v, w]: adj[u]) {
            if (tot[v].size() < k) pq.push({-(cost + w), v});
        }
    }
 
    vector<int> ans;
    while(!tot[n].empty()){
        ans.push_back(tot[n].top());
        tot[n].pop();
    }
    sort(ans.begin(), ans.end());
    for(auto x : ans) cout << x << ' ';
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
