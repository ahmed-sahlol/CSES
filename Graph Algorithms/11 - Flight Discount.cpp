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
const int N=2e5+5,oo=1e18;
int n,m,dist[N][2];vector<pair<int,int>>adj[N];
void dijkstra(int src)
{
    for(int i=1;i<=n;i++) dist[i][0]=dist[i][1]=oo;
    //   cost     node  coupon
    priority_queue<pair<int,pair<int,bool>>,
            vector<pair<int,pair<int,bool>>>,
                    greater<pair<int,pair<int,bool>>>>pq;
    pq.push({0,{src,1}});
    dist[src][1]=dist[src][0]=0;
    while(!pq.empty())
    {
        int node=pq.top().second.first;
        bool coupon=pq.top().second.second;
        int cost=pq.top().first;
        pq.pop();
        if(dist[node][coupon]<cost) continue;
        for(auto [child,price] : adj[node])
        {
            if(dist[child][coupon]>cost+price)
            {
                dist[child][coupon]=cost+price;
                pq.push({dist[child][coupon],{child,coupon}});
            }
            if(coupon)
            {
                if(dist[child][0]>cost+(price/2))
                {
                    dist[child][0]=cost+(price/2);
                    pq.push({dist[child][0],{child,0}});
                }
            }
        }
    }
}
signed main()
{
    __();
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v,c;cin>>u>>v>>c;
        adj[u].push_back({v,c});
    }
    dijkstra(1);
    cout<<min(dist[n][1],dist[n][0])<<el;
    return 0;
}
