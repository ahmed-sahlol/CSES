#include <bits/stdc++.h>
#define ll long long
#define el '\n'
using namespace std;
const int N=2e5+5;
int n,m,dis[N],pare[N];vector<int>adj[N];bool vis[N],ok;
void bfs()
{
    dis[1]=0;
    pare[1]=-1;
    queue<ll>q;
    q.push(1);
    while(!q.empty())
    {
        int node=q.front();q.pop();
        if(node==n)
        {
            ok=1;
            return;
        }
        for(auto it: adj[node])
        {
            if(!vis[it])
            {
                vis[it]=1;
                dis[it]=dis[node]+1;
                pare[it]=node;
                q.push(it);
            }
        }
    }
}
signed main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m;
    while (m--)
    {
        int a,b;cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    bfs();
    if(ok)
    {
        cout<<dis[n]+1<<el;
        stack<int>st;
        int h=pare[n];
        while(true)
        {
            st.push(h);
            if(h==1) break;
            h=pare[h];
        }
        while(!st.empty())
        {
            cout<<st.top()<<' ';
            st.pop();
        }
        cout<<n<<el;
    }
    else cout<<"IMPOSSIBLE"<<el;
    return 0;
}
