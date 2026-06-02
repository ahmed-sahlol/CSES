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
 
void work() {
    string s;
    cin >> s;
    auto z = zFunction(s);
    int n = s.size();
    for (int i = 0; i < n; ++i)
        if (z[n - i - 1] == i + 1) cout << i + 1 << ' ';
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
