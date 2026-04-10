#include <bits/stdc++.h>
#define ll long long
#define el '\n'
using namespace std;
const int N=2e5+5;
int n,ans,sz[N];vector<int>adj[N];bool vis[N];
void dfs(int node,int have)
{
    vis[node]=1;
    sz[node]=have;
    for(auto it: adj[node])
    {
        if(!vis[it])
        {
           dfs(it,have+1);
        }
    }
}
signed main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=2;i<=n;i++)
    {
        int a,b;cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,0);
    int node=0,szi=0;
    for(int i=1;i<=n;i++)
    {
        if(sz[i]>=szi)
        {
            node=i;
            szi=sz[i];
        }
    }
    memset(sz,0,sizeof sz);
    memset(vis,0,sizeof vis);
    dfs(node,0);
    cout<<*max_element(sz,sz+n)<<el;
    return 0;
}
