#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
// Patterns must be distinct
struct AhoCorasick {
    // Number of nodes & Number of patterns
    int N, P;
 
    /// Change this for the patterns structure
    const int A = 26;
    const char neutral = 'a';
 
    vector<vector<int>> next;
    vector<int> link, out_link;
    vector<vector<int>> out;
 
    /*
     * next : Normal trie links
     * link : Longest proper prefix equals to this suffix
     * out_link : First suffix that has a match in it
     * out : the indices of the matched patterns in this node
    */
 
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
    }
 
    int advance(int u, char c) {
        while (u && !next[u][get(c)]) u = link[u];
        u = next[u][get(c)];
        return u;
    }
};
 
const int mod = 1e9 + 7;
 
void work() {
    int n;
    string me;
    cin >> me >> n;
    vector<string> patt(n);
    for (auto &i: patt) cin >> i;
 
    AhoCorasick Aho;
    vector<string> good_pattern;
    for (auto cur: patt) {
        Aho.add_pattern(cur);
        good_pattern.push_back(cur);
    }
    Aho.compute();
 
    vector<int> dp(me.size() + 10, 0);
    dp[0] = 1;
 
    int node = 0;
    for (int i = 0; i < me.size(); ++i) {
        char ch = me[i];
        node = Aho.advance(node, ch);
        for (int v = node; v; v = Aho.out_link[v]) {
            for (auto idx: Aho.out[v]) {
                int sz = good_pattern[idx].size();
                int prev = i + 1 - sz;
                if (prev >= 0 && dp[prev] > 0) dp[i + 1] = (dp[i + 1] + dp[prev]) % mod;
            }
        }
    }
 
    cout << dp[me.size()] << el;
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
