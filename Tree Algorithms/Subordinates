#include <bits/stdc++.h>
#define ll long long
#define el '\n'
using namespace std;
const int N=2e5+5;
int n,ans,sz[N];vector<int>adj[N];bool vis[N];
void dfs(int node)
{
    vis[node]=1;
    sz[node]=1;
    for(auto it: adj[node])
    {
        if(!vis[it])
        {
           ans++;
           dfs(it);
           sz[node]+=sz[it];
        }
    }
}
signed main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=2;i<=n;i++)
    {
        int a;cin>>a;
        adj[a].push_back(i);
    }
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])dfs(i);
    }
    for(int i=1;i<=n;i++) cout<<sz[i]-1<<' ';
    return 0;
}
