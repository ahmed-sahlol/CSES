#include <bits/stdc++.h>
#define ll long long
#define el '\n'
using namespace std;
const int N=1e3+4;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
const char know[]={'D','U','R','L'};
int n,m,starm,starmm,endx,endy,sz;vector<vector<char>>v(N,vector<char>(N));bool ok;
bool vaild(int i,int j)
{
    return i>=0&&i<n&&j>=0&&j<m&&(v[i][j]=='B'||v[i][j]=='.');
}
void bfs(int starx,int stary)
{
    queue<pair<ll,pair<int,int>>>q;
    q.push({0,{starx,stary}});
    while(!q.empty())
    {
        int x1=q.front().second.first,x2=q.front().second.second;
        int cost=q.front().first;
        q.pop();
        if(x1==endx&&x2==endy)
        {
            ok=1;
            sz=cost;
            return;
        }
        for(int o=0;o<4;o++)
        {
            int nx=dx[o]+x1,ny=dy[o]+x2;
            if(vaild(nx,ny))
            {
                v[nx][ny]=know[o];
                q.push({cost+1,{nx,ny}});
            }
        }
    }
}
signed main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=0;i<n;i++) for(int j=0;j<m;j++)
        {
            cin>>v[i][j];
            if(v[i][j]=='A') starm=i,starmm=j;
            else if(v[i][j]=='B')  endx=i,endy=j;
        }
    bfs(starm,starmm);
    if(ok)
    {
        cout<<"YES"<<el<<sz<<el;
        string ans="";
        int i=endx,j=endy;
        while(i!=starm||j!=starmm)
        {
            ans+=v[i][j];
            if(v[i][j]=='U') i=i+1;
            else if(v[i][j]=='D')i=i-1;
            else if(v[i][j]=='L')j=j+1;
            else if(v[i][j]=='R')j=j-1;
        }
        reverse(ans.begin(),ans.end());
        cout<<ans<<el;
    }
    else cout<<"NO"<<el;
    return 0;
}
