#include <bits/stdc++.h>
#define int long long
#define el '\n'
using namespace std;
void __()
{
#ifndef ONLINE_JUDGE
    freopen("D:\\TEST\\Input.txt", "r", stdin);
    freopen("D:\\TEST\\Output.txt", "w", stdout);
#endif
}
const int N=1000, oo = 1e18;
int floyd[N][N];
int n,m,q;
void build()
{
    for(int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                floyd[i][j] = min(floyd[i][j], floyd[i][k] + floyd[k][j]);
            }
        }
    }
}
signed main()
{
    __();
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m>>q;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++) floyd[i][j]=(i==j?0:oo);
    for(int i=1;i<=m;i++)
    {
        int a,b,c;cin>>a>>b>>c;
        a--,b--;
        floyd[a][b]=min(floyd[a][b],c);
        floyd[b][a]=min(floyd[b][a],c);
    }
    build();
    while(q--)
    {
        int a,b;cin>>a>>b;a--,b--;
        cout<<(floyd[a][b]==oo?-1:floyd[a][b])<<el;
    }
    return 0;
}
