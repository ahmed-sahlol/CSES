#include <bits/stdc++.h>
#define ll long long
#define el '\n'
#define ld long double
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
using namespace std;
int const N=1e3+10;
const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};
int n,m,ans;char arr[N][N];
bool vaild(int o,int k)
{
    return arr[o][k]=='.'&&o>=0&&k>=0&&o<n&&k<m;
}
void dfs(int x,int y)
{
    arr[x][y]='#';
    for(int k=0;k<4;k++)
    {
        int nx=x+dx[k],ny=y+dy[k];
        if(vaild(nx,ny)) dfs(nx,ny);
    }
}
signed main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin>>arr[i][j];
     for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(vaild(i,j))
            {
                ans++;
                dfs(i,j);
            }
        }
    }
    cout<<ans<<el;
    return 0;
}
