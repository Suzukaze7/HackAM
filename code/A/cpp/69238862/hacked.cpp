#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <tuple>
#include <bitset>
using namespace std;
using T=tuple<int,int,int,int>;
const int dx[4]={-1,0,1,0};
const int dy[4]={0,-1,0,1};
const int N=1010;
string a[N];
int b[N][N][4];
int n,m;
int sx,sy,ex,ey;
bool check(int x,int y)
{
	return 0<=x&&x<n&&0<=y&&y<m;
}
int bfs()
{
	int x,y,z,w,nx,ny,nz,i;
	priority_queue<T,vector<T>,greater<T>> q;
	memset(b,0x3f,sizeof(b));
	for(i=0;i<4;++i)
	{
		q.emplace(1,sx,sy,i);
		b[sx][sy][i]=1;
	}
	while(!q.empty())
	{
		tie(w,x,y,z)=q.top();
		q.pop();
		nx=x+dx[z];
		ny=y+dy[z];
		if(w>=b[nx][ny][z]||!check(nx,ny))
			continue;
		if(a[nx][ny]=='#')
		{
			if(x==ex&&y==ey)
				return w;
			for(i=0;i<4;++i)
				if((i+z)%2==1&&w+1<b[x][y][i])
				{
					q.emplace(w+1,x,y,i);
					b[x][y][i]=w+1;
				}
		}
		else
		{
			q.emplace(w,nx,ny,z);
			b[nx][ny][z]=w;
		}
	}
	return -1;
}
int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int i,j;
	cin>>n>>m;
	for(i=0;i<n;++i)
		cin>>a[i];
	for(i=0;i<n;++i)
		for(j=0;j<m;++j)
		{
			if(a[i][j]=='S')
				sx=i,sy=j;
			if(a[i][j]=='T')
				ex=i,ey=j;
		}
	cout<<bfs();
	return 0;
}