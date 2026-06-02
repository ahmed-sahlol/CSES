#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
struct Manacher {
// P[i] : the radius of the longest palindrome centered at t[i] , t is one base
// P[2 * j + 1] : palindrome info for jth character in string s , zero base
// P[2 * j + 2] : palindrome info for the gap between j , j + 1 in string s
    vector<int> p;
 
    void build(string &s) {
        string t;
        for (auto &val: s)t += '#', t += val;
        t += '#';
        int n = (int) t.size();
        p.resize(n, 1);
        int l = 1, r = 1;
        for (int i = 1; i < n; i++) {
            p[i] = max(0LL, min(r - i, p[l + r - i]));
            while (i - p[i] >= 0 and i + p[i] < n and t[i + p[i]] == t[i - p[i]])p[i]++;
            if (p[i] + i > r) {
                r = i + p[i];
                l = i - p[i];
            }
        }
    }
 
    int GetLongest(int center, bool odd = true) {
        int NewCenter = 2 * center + !odd + 1;
        return p[NewCenter] - 1;
    }
 
    bool IsPalndrome(int l, int r) {
        return (r - l + 1) <= GetLongest((l + r) / 2, l % 2 == r % 2);
    }
};
 
void work() {
    string s;
    cin >> s;
    Manacher m;
    m.build(s);
    int mx = 0;
    for (int i = 0; i < s.size(); ++i) {
        mx = max(mx, m.GetLongest(i, 0));
        mx = max(mx, m.GetLongest(i, 1));
    }
    for (int i = 0; i < s.size(); ++i) {
        if (m.GetLongest(i, 0) == mx) {
            cout << s.substr(i - mx / 2 + 1, mx) << el;
            return;
        }
 
        if (m.GetLongest(i, 1) == mx) {
            cout << s.substr(i - mx / 2, mx) << el;
            return;
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
