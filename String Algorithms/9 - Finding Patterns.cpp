#include <bits/stdc++.h>
 
#define int long long
 
#define el '\n'
 
using namespace std;
 
struct AhoCorasick {
    enum {
        alpha = 26, first = 'a'
    };
 
    struct Node {
        int nxt[alpha]; /// Next state transition for each character
        int suflink = 0; /// Suffix link points to longest proper suffix
        int start = -1; /// Start index of pattern in original array
        int end = -1; /// Index in backup of longest matched suffix pattern
        int nmatches = 0; ///Count of matched strings ending at this node
        int lvl = 0;
 
        Node(int v) {
            memset(nxt, v, sizeof nxt);
        }
    };
 
    vector<Node> v; /// Stores all nodes of the trie
    vector<int> backup;

    void insert(string &s, int id) {
        int node = 0;
        int clvl = 0;
        for (auto &c: s) {
            int &m = v[node].nxt[c - first];
            ++clvl;
            if (m == -1) {
                node = m = v.size();
                v.emplace_back(-1);
                v.back().lvl = clvl;
            } else node = m;
        }
        if (v[node].end == -1) v[node].start = id;
        backup.emplace_back(v[node].end);
        v[node].end = id;
        v[node].nmatches++;
    }
 
    AhoCorasick(vector<string> &pat) : v(1, -1) {
        for (int i = 0; i < pat.size(); ++i)insert(pat[i], i);
        v[0].suflink = v.size();
        v.emplace_back(0);
        queue<int> q;
        q.push(0);
        while (q.size()) {
            int node = q.front();
            q.pop();
            int prv = v[node].suflink;
            for (int i = 0; i < alpha; ++i) {
                int &x = v[node].nxt[i], y = v[prv].nxt[i];
                if (x == -1) {
                    x = y;
                    continue;
                }
                v[x].suflink = y;
                (v[x].end == -1 ? v[x].end : backup[v[x].start]) = v[y].end;
                v[x].nmatches += v[y].nmatches;
                q.push(x);
            }
        }
    }
};
 
void work() {
    int q;
    string s;
    cin >> s >> q;
 
    vector<string> patt(q), res(q, "NO");
    for (auto &i: patt) cin >> i;
 
    AhoCorasick Aho(patt);
 
    int node = 0;
    for (char ch: s) {
        node = Aho.v[node].nxt[ch - 'a'];
        int id = Aho.v[node].end;
        while (id != -1) {
            if (res[id] == "YES") break;
            res[id] = "YES";
            id = Aho.backup[id];
        }
    }
 
    for (auto i: res) cout << i << el;
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
