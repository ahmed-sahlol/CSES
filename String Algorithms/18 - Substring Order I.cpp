#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
struct Suffix_array {
    int n;
    string s;
    vector<int> p, c, lcp;
 
    Suffix_array(string in) {
        s = in + "$";
        n = s.size();
        p.assign(n + 1, 0);
        c.assign(n + 1, 0);
        build0();
        buildk();
        lcp.assign(n, 0);
        LCP();
    }
 
    void build0() {
        vector<pair<char, int>> a;
        for (int i = 0; i < n; ++i) a.push_back({s[i], i});
        sort(a.begin(), a.end());
 
        for (int i = 0; i < n; ++i) p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; ++i) {
            if (a[i].first != a[i - 1].first) c[p[i]] = c[p[i - 1]] + 1;
            else c[p[i]] = c[p[i - 1]];
        }
    }
 
    void count_sort() {
        vector<int> freq(n), p_new(n), pos(n);
        for (int i = 0; i < n; ++i) ++freq[c[i]];
 
        pos[0] = 0;
        for (int i = 1; i < n; ++i)
            pos[i] = pos[i - 1] + freq[i - 1];
 
        for (int i = 0; i < n; ++i) p_new[pos[c[p[i]]]] = p[i], ++pos[c[p[i]]];
 
        p = p_new;
    }
 
    void buildk() {
        int k = 0;
        while ((1LL << k) < n) {
            vector<int> c_new(n);
            for (int i = 0; i < n; ++i) p[i] = ((p[i] - (1LL << k)) + n) % n;
            count_sort();
            c_new[p[0]] = 0;
            for (int i = 1; i < n; ++i) {
                pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1LL << k)) % n]};
                pair<int, int> now = {c[p[i]], c[(p[i] + (1LL << k)) % n]};
                if (now != prev) c_new[p[i]] = c_new[p[i - 1]] + 1;
                else c_new[p[i]] = c_new[p[i - 1]];
            }
            c = c_new;
            ++k;
        }
    }
 
    void LCP() {
        int k = 0;
        for (int i = 0; i < n - 1; ++i) {
            int pi = c[i];
            int j = p[pi - 1];
            while (s[i + k] == s[j + k])++k;
            lcp[pi] = k;
            k = max(k - 1, 0LL);
        }
    }
};
 
void work() {
    string s;
    int k;
    cin >> s;
    cin >> k;
    Suffix_array suff(s);
    int ans = 0;
    for (int i = 1; i <= s.size(); ++i) {
        int x = s.size() - suff.p[i];
        x -= suff.lcp[i];
        if (k > x) k -= x;
        else {
            cout << s.substr(suff.p[i], k + suff.lcp[i]) << el;
            break;
        }
    }
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
