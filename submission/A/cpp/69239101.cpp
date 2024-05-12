#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
#define lowbit(x) ((x)&(-(x)))
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define maxheap(x) priority_queue<x,vector<x>,less<x> > 
#define minheap(x) priority_queue<x,vector<x>,greater<x> > 
#define endl '\n'
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;
typedef long long ll;
typedef unsigned long long ull;
//#define mod 1000000009
//#define mod 1000000007
char mp[1005][1005];
int dis[1005][1005];
int vis[1005][1005];
int dx[]={0,0,1,-1};//右，左，下，上
int dy[]={1,-1,0,0};
int nxt[1005][1005][4];
int main()
{
    int n,m;
    cin>>n>>m;
    int i,j;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++) cin>>mp[i][j];
    }
    int x,y;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            nxt[i][j][1]=nxt[i][j-1][1];
            if(mp[i][j]=='#') nxt[i][j][1]=0;
            else if(mp[i][j-1]&&mp[i][j-1]!='#') nxt[i][j][1]++;
        }
    }
    for(i=1;i<=n;i++)
    {
        for(j=m;j>=1;j--)
        {
            nxt[i][j][0]=nxt[i][j+1][0];
            if(mp[i][j]=='#') nxt[i][j][0]=0;
            else if(mp[i][j+1]&&mp[i][j+1]!='#') nxt[i][j][0]++;
        }
    }
    for(i=1;i<=m;i++)
    {
        for(j=1;j<=n;j++)
        {
            nxt[j][i][3]=nxt[j-1][i][3];
            if(mp[j][i]=='#') nxt[j][i][3]=0;
            else if(mp[j-1][i]&&mp[j-1][i]!='#') nxt[j][i][3]++;
        }
    }
    for(i=1;i<=m;i++)
    {
        for(j=n;j>=1;j--)
        {
            nxt[j][i][2]=nxt[j+1][i][2];
            if(mp[j][i]=='#') nxt[j][i][2]=0;
            else if(mp[j+1][i]&&mp[j+1][i]!='#') nxt[j][i][2]++;
        }
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            if(mp[i][j]=='S')
            {
                x=i,y=j;
            }
        }
     }
    memset(dis,0x3f,sizeof(dis));
    dis[x][y]=0;
    queue<PII> q;
    q.push({x,y});
    while(!q.empty())
    {
        auto tmp=q.front();
        q.pop();
        int x=tmp.first;
        int y=tmp.second;
        if(vis[x][y]) continue;
        vis[x][y]=1;
        for(i=0;i<4;i++)
        {
            if(!nxt[x][y][i]) continue;
            int xx,yy;
            if(i==0)
            {
                if(vis[x][y+nxt[x][y][0]]) continue;
                xx=x;
                yy=y+nxt[x][y][0];
            }
            if(i==1)
            {
                if(vis[x][y-nxt[x][y][1]]) continue;
                xx=x;
                yy=y-nxt[x][y][1];
            }
            if(i==2)
            {
                if(vis[x+nxt[x][y][2]][y]) continue;
                xx=x+nxt[x][y][2];
                yy=y;
            }
            if(i==3)
            {
                if(vis[x-nxt[x][y][3]][y]) continue;
                xx=x-nxt[x][y][3];
                yy=y;
            }
            if(vis[xx][yy]) continue;
            dis[xx][yy]=min(dis[x][y]+1,dis[xx][yy]);
            q.push({xx,yy});
        }
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            if(mp[i][j]=='T')
            {
                x=i,y=j;
                break;
            }
        }
    }
    if(dis[x][y]!=INF) cout<<dis[x][y];
    else cout<<-1;
         return 0;
}