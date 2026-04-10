#include <bits/stdc++.h>
#define ll long long
#define el '\n'
using namespace std;
const int N=2e5+5;
int n,ans,sz1[N],sz2[N];vector<int>adj[N];bool vis[N];
void dfs(int node,int have)
{
    vis[node]=1;
    sz1[node]=have;
    for(auto it: adj[node])
    {
        if(!vis[it])
        {
           dfs(it,have+1);
        }
    }
}
void dfs1(int node,int have)
{
    vis[node]=1;
    sz2[node]=have;
    for(auto it: adj[node])
    {
        if(!vis[it])
        {
            dfs1(it,have+1);
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
    int nodee=INT_MIN,ma=INT_MIN;
    for(int i=1;i<=n;i++)
    {
        if(sz1[i]>=ma)
        {
            nodee=i;
            ma=sz1[i];
        }
    }
    memset(vis,0,sizeof vis);
    dfs(nodee,0);
    ma=INT_MIN;
    for(int i=1;i<=n;i++)
    {
        if(sz1[i]>=ma)
        {
            nodee=i;
            ma=sz1[i];
        }
    }
    memset(vis,0,sizeof vis);
    dfs1(nodee,0);
    for(int i=1;i<=n;i++) cout<<max(sz1[i],sz2[i])<<' ';
    return 0;
}
