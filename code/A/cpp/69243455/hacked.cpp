#include<bits/stdc++.h>
using namespace  std;
typedef long long ll;
const int N=1000+10;
char a[N][N];
int startx,starty,endx,endy;
bool st[N][N];
ll ans=1e18;
int flag=1;
int n,m;
typedef pair<int,int > pll;
map<pll,int > mp;
queue<pll> q;
ll ens=0;
void bfs()
{
    while(q.size())
    {
       pll t=q.front();
        q.pop();
        int x=t.first,y=t.second;
        if(x==endx&&y==endy)
        {
            ans=mp[{x,y}];
            flag=0;
            return;
        }
        int x1,y1;
        for(int i=1;i<=4;i++)
        {
                if(i==1)
            {
                x1=x,y1=y;
                while(a[x1-1][y1]!='#') x1--;
                if(!st[x1][y1])
                {
                    st[x1][y1]=1;
                    q.push({x1,y1});
                    mp[{x1,y1}]=mp[{x,y}]+1;
                }
            }
            if(i==2)
            {
                x1=x,y1=y;
                while(a[x1+1][y1]!='#') x1++;
                if(!st[x1][y1])
                {
                    st[x1][y1]=1;
                    q.push({x1,y1});
                    mp[{x1,y1}]=mp[{x,y}]+1;
                }
            }
            if(i==3)
            {
                x1=x,y1=y;
                while(a[x1][y1-1]!='#') y1--;
                if(!st[x1][y1])
                {
                    st[x1][y1]=1;
                    q.push({x1,y1});
                    mp[{x1,y1}]=mp[{x,y}]+1;
                }
            }
            if(i==4)
            {
                x1=x,y1=y;
                while(a[x1][y1+1]!='#') y1++;
                if(!st[x1][y1])
                {
                    st[x1][y1]=1;
                    q.push({x1,y1});
                    mp[{x1,y1}]=mp[{x,y}]+1;
                }
            }
        }
        }
	
}
void solve()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		cin>>a[i][j];
		if(a[i][j]=='S')
		{
			startx=i,starty=j;
		}
		if(a[i][j]=='T')
		{
			endx=i,endy=j;
		}
	}
    if(a[endx+1][endy]=='.'&&a[endx-1][endy]=='.'&&a[endx][endy+1]=='.'&&a[endx][endy-1]=='.')
    {
        cout<<"-1"<<endl;
        return;
    }
    st[startx][starty]=1;
    mp[{startx,starty}]=0;
        q.push({startx,starty});
        bfs();
	   if(flag) 
       {
           cout<<"-1"<<endl;
       }else{
           cout<<ans<<endl;
       }
	
}
int main()
{
	int t;
	t=1;
	while(t--)
	{
	solve();
	}
	return 0;
}
