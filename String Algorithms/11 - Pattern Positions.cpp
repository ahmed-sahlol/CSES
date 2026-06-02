#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
struct AhoCorasick {
    int N, P;
     const int A = 26;
    const char neutral = 'a';
 
    vector<vector<int>> next;
    vector<int> link, out_link;
    vector<vector<int>> out;
    vector<vector<int>> dp;
 
    AhoCorasick() : N(0), P(0) { node(); }
 
    int node() {
        next.emplace_back(A, 0);
        link.emplace_back(0);
        out_link.emplace_back(0);
        out.emplace_back(0);
        return N++;
    }
 
    inline int get(char c) { return c - neutral; }
 
    int add_pattern(const string &patt) {
        int u = 0;
        for (auto &c: patt) {
            if (!next[u][get(c)]) next[u][get(c)] = node();
            u = next[u][get(c)];
        }
        out[u].push_back(P);
        return P++;
    }
 
    void compute() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int c = 0; c < A; ++c) {
                int v = next[u][c];
                if (!v) next[u][c] = next[link[u]][c];
                else {
                    link[v] = u ? next[link[u]][c] : 0;
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
        dp.assign(N, vector<int>(A, -1));
    }
 
    int advance(int u, char c) {
        if (!u || next[u][get(c)]) return next[u][get(c)];
        if (~dp[u][get(c)]) return dp[u][get(c)];
        int &ret = dp[u][get(c)];
        ret = advance(link[u], c);
        return ret;
    }
};
 
void work() {
    int q;
    string s;
    cin >> s >> q;
 
    vector<string> patt(q);
    vector<int> res(q, 0);
    for (auto &i: patt) cin >> i;
 
    AhoCorasick aho;
    map<string, int> mp;
    vector<string> rev_id;
    for (auto curr: patt) {
        if (mp.count(curr)) continue;
        mp[curr] = aho.add_pattern(curr);
        rev_id.push_back(curr);
    }
 
    aho.compute();
 
    int node = 0;
    vector<int> id(mp.size() + 1, 1e9);
    for (int i = 0; i < s.size(); ++i) {
        char ch = s[i];
        node = aho.advance(node, ch);
        for (int v = node; v; v = aho.out_link[v]) {
            for (auto idx: aho.out[v])
                id[idx] = min(id[idx], i - (int) rev_id[idx].size() + 1);
        }
    }
 
    for (auto x: patt) cout << (id[mp[x]] == 1e9 ? -1 : id[mp[x]] + 1) << el;
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
