#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
struct Hash {
    int h1, h2, sz, base1, base2, mod1, mod2, inv1, inv2;
 
    vector<int> pw1, pw2;
    deque<char> lst;
    vector<pair<int, int>> prefix;
 
    long long fastpowermod(int a, int b, int mod) {
        int ret = 1;
        while (b > 0) {
            if (b & 1) ret = (ret * a) % mod;
            ret = (ret * ret) % mod;
            b >>= 1;
        }
        return ret;
    }
 
    Hash(int n) {
        h1 = h2 = sz = 0;
        base1 = 31, base2 = 37, mod1 = 1e9 + 7, mod2 = 2e9 + 11;
        pw1.assign(n + 5, 0);
        pw2.assign(n + 5, 0);
        prefix.assign(n + 5, {0, 0});
        inv1 = fastpowermod(base1, mod1 - 2, mod1),
        inv2 = fastpowermod(base2, mod2 - 2, mod2),
        pw1[0] = pw2[0] = 1;
        for (int i = 1; i <= n; ++i) {
            pw1[i] = (pw1[i - 1] * base1) % mod1;
            pw2[i] = (pw2[i - 1] * base2) % mod2;
        }
    }
 
    void push_back(char c) {
        int num = (c - 'a') + 1;
        h1 = (h1 * base1) % mod1;
        h1 = (h1 + num) % mod1;
        h2 = (h2 * base2) % mod2;
        h2 = (h2 + num) % mod2;
        lst.push_back(c);
        sz++;
    }
 
    void pop_back() {
        if (sz == 0) return;
        int num = (lst.back() - 'a') + 1;
        h1 = (h1 - num + mod1) % mod1;
        h1 = (h1 * inv1) % mod1;
        h2 = (h2 - num + mod2) % mod2;
        h2 = (h2 * inv2) % mod2;
        sz--;
        lst.pop_back();
    }
 
    void push_front(char c) {
        int num = (c - 'a') + 1;
        h1 = (h1 + (num * pw1[sz]) % mod1) % mod1;
        h2 = (h2 + (num * pw2[sz]) % mod2) % mod2;
        sz++;
        lst.push_front(c);
    }
 
    void pop_front() {
        if (sz == 0) return;
        int num = (lst.front() - 'a') + 1;
        h1 = ((h1 - num * pw1[sz - 1] % mod1) + mod1) % mod1;
        h2 = ((h2 - num * pw2[sz - 1] % mod2) + mod2) % mod2;
        lst.pop_front();
        sz--;
    }
 
    pair<int, int> GetHash() {
        return {h1, h2};
    }
 
 
    void build_prefix(string s) {
        for (int i = 0; i < s.size(); ++i) {
            push_back(s[i]);
            prefix[i] = GetHash();
        }
    }
 
 
    pair<int, int> query_prefix(int l, int r) { // base 0 [l,r]
        pair<int, int> ans = prefix[r];
        int len = r - l + 1;
        if (l) {
            ans.first -= (prefix[l - 1].first * pw1[len]) % mod1;
            if (ans.first < 0) ans.first += mod1;
            ans.second -= (prefix[l - 1].second * pw2[len]) % mod2;
            if (ans.second < 0) ans.second += mod2;
        }
        return ans;
    }
 
    void clear() {
        h1 = h2 = 0;
        lst.clear();
    }
};
 
void work() {
    string s;
    cin >> s;
    int n = s.size();
    Hash h(n);
    h.build_prefix(s);
    vector<int> ans;
    for (int len = 1; len <= n; ++len) {
        bool ok = 1;
        int idx = 0;
        while (idx < n && ok) {
            int add = min(n - idx, len);
            ok &= (h.query_prefix(0, add - 1) == h.query_prefix(idx, idx + add - 1));
            idx += add;
        }
        if (ok) ans.push_back(len);
    }
 
    for (auto i: ans) cout << i << ' ';
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
    while (tc--) {
        work();
    }
}
