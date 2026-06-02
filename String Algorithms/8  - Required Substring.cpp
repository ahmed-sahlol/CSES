#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
vector<int> kmp(const string &s) {
    const int n = (int) s.length();
    vector<int> fail(n);
    int j = 0;
    for (int i = 1; i < n; i++) {
        while (j > 0 && s[i] != s[j]) j = fail[j - 1];
        j += (s[j] == s[i]);
        fail[i] = j;
    }
    return fail;
}
 
void compute_automaton(string s, vector<vector<int>> &aut) {
    s += '#';
    int n = s.size();
    vector<int> pi = kmp(s);
    aut.assign(n, vector<int>(26));
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
            if (i > 0 && 'a' + c != s[i]) {
                aut[i][c] = aut[pi[i - 1]][c];
            } else {
                aut[i][c] = i + ('a' + c == s[i]);
            }
        }
    }
}
 
const int mod = 1e9 + 7;
 
long long mul(long long a, long long b) { return ((a % mod) * (b % mod)) % mod; }
 
long long fastpowermod(long a, long b) {
    if (b == 0) return 1;
    if (b == 1) return a;
    long long ret = fastpowermod(a, b / 2);
    ret = mul(ret, ret);
    if (b & 1) ret = mul(ret, a);
    return ret;
}
 
void work() {
    int n;
    string s;
    cin >> n >> s;
    int m = s.size();
    for (auto &c: s)c = tolower(c);
    vector<vector<int>> aut;
    compute_automaton(s, aut);
    vector<vector<int>> dp(n + 5, vector<int>(m + 5, -1));
    function<int(int, int)> solve = [&](int i, int j) -> int {
        if (j == m) return fastpowermod(26, n - i);
        if (i == n) return 0;
        int &ret = dp[i][j];
        if (~ret) return ret;
        ret = 0;
        for (int c = 0; c < 26; ++c) {
            ret += solve(i + 1, aut[j][c]);
            if (ret >= mod) ret %= mod;
        }
        return ret;
    };
 
    cout << solve(0, 0) << el;
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
