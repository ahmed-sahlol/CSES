#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
void work() {
    int n, m;
    cin >> n >> m;
    char arr[n + 3][m + 3];
    int dx[4] = {1, -1, 0, 0},
            dy[4] = {0, 0, 1, -1};
 
    vector<vector<int>> dist(n + 2, vector<int>(m + 2, INT32_MAX));
    vector<vector<int>> distme(n + 2, vector<int>(m + 2, INT32_MAX));
    vector<vector<int>> par(n + 2, vector<int>(m + 2, -1));
    queue<pair<int, int>> monsters, me;
 
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> arr[i][j];
            if (arr[i][j] == 'M') {
                monsters.push({i, j});
                dist[i][j] = 0;
            }
            if (arr[i][j] == 'A') {
                me.push({i, j});
                distme[i][j] = 0;
            }
        }
    }
 
    auto valid = [&](int i, int j) -> bool {
        return (i >= 0 && i < n && j >= 0 && j < m);
    };
 
    while (monsters.size()) {
        int r = monsters.front().first, c = monsters.front().second;
        int cost = dist[r][c];
        monsters.pop();
        for (int k = 0; k < 4; ++k) {
            int nwx = dx[k] + r, nwy = dy[k] + c;
            if (valid(nwx, nwy) && arr[nwx][nwy] != '#' && dist[nwx][nwy] > cost + 1) {
                dist[nwx][nwy] = cost + 1;
                monsters.push({nwx, nwy});
            }
        }
    }
 
    map<int, char> mp;
    mp[0] = 'D';
    mp[1] = 'U';
    mp[2] = 'R';
    mp[3] = 'L';
 
    while (me.size()) {
        int r = me.front().first, c = me.front().second;
        int cost = distme[r][c];
        me.pop();
        for (int k = 0; k < 4; ++k) {
            int nwx = dx[k] + r, nwy = dy[k] + c;
            if (!valid(nwx, nwy) && dist[r][c] > distme[r][c]) {
                cout << "YES" << el;
                cout << cost << el;
                string s = "";
                int nowr = r, nowc = c;
                while (par[nowr][nowc] != -1) {
                    int x = par[nowr][nowc];
                    if (x == 0) s += 'D', nowr--;
                    if (x == 1) s += 'U', nowr++;
                    if (x == 2) s += 'R', nowc--;
                    if (x == 3) s += 'L', nowc++;
                }
                reverse(s.begin(), s.end());
                cout << s << el;
                return;
            }
            if (valid(nwx, nwy) && arr[nwx][nwy] != '#' && distme[nwx][nwy] > cost + 1) {
                distme[nwx][nwy] = cost + 1;
                me.push({nwx, nwy});
                par[nwx][nwy] = k;
            }
        }
    }
 
    cout << "NO" << el;
}
 
int32_t main() {
#ifndef ONLINE_JUDGE
    freopen("D:\\test\\input.txt", "r", stdin);
    freopen("D:\\test\\output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int tc = 1;
//    cin >> tc;
    for (int T = 1; T <= tc; ++T) {
//        cout << "Case " << T << ":" << el;
        work();
    }
}
