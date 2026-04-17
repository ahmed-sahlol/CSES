#include <bits/stdc++.h>
#define ll long long
#define el '\n'
using namespace std;
const int N=2e5+5;
int n,m,ans[N];vector<int>adj[N];bool ok;
void dfs(int node,int parent)
{
    for(auto it: adj[node])
    {
        if(ans[it]&&ans[it]==ans[node])
        {
            ok=1;
            return;
        }
        if(!ans[it])
        {
            ans[it]=3-ans[node];
            dfs(it,node);
        }
    }
}
void I_Can_Problem_colving()
{
    cin>>n>>m;
    while(m--)
    {
        int u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=1;i<=n;i++) if(!ans[i]) ans[i]=1,dfs(i,-1);
    if(ok)
    {
        cout<<"IMPOSSIBLE"<<el;
        return;
    }
 
    for (int i = 1; i <=n ; ++i)
    {
        cout<<ans[i]<<' ';
    }
}
signed main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("C:\\Go to ACPC\\input.txt", "r", stdin);
    freopen("C:\\Go to ACPC\\output.txt", "w", stdout);
#endif
    int t=1;//cin>>t;
    for(int i=1;i<=t;i++)
    {
        I_Can_Problem_colving();/*   ===> (   ICPC   )    */
    }
    return 0;
}
