#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
vector<int> zFunction(string s) {
    // z[i] starts at i what is the largest string is matching a prefix
    int n = s.size();
    vector<int> z(n);
    int left = 0, right = 0;
    for (int i = 1; i < n; i++) {
        if (i <= right) z[i] = min(right - i + 1, z[i - left]);
        while (i + z[i] < n && s[z[i]] == s[z[i] + i]) z[i]++;
        if (i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }
    return z;
}
 
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
 
void work() {
    string s;
    cin >> s;
    auto z = zFunction(s);
    for (auto i: z)cout << i << ' ';
    cout << el;
    auto k = kmp(s);
    for (auto i: k)cout << i << ' ';
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
