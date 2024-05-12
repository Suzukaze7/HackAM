#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10,M=2*N,mod=1e9+7;
#define uLL unsigned long long
const int inf=1e18;
typedef pair<int,int> PII;
typedef long long LL;
using node=tuple<int,int,int>;
int n,m,k;
int dist[2010][2010][5];
char g[5010][5010];
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
bool st[2010][2010][5];
void solve()
{
   cin>>n>>m;
   deque<node> q;
   int ex,ey;
   memset(dist,0x3f,sizeof(dist));
   for(int i=1;i<=n;i++){
       for(int j=1;j<=m;j++){
           cin>>g[i][j];
           if(g[i][j]=='S'){
               for(int k=0;k<4;k++)
               {
                   q.emplace_front(i,j,k);
                   dist[i][j][k]=1;
               }
           }
           if(g[i][j]=='T'){
               ex=i;ey=j;
           }
       }
   }
   while(q.size()){
       auto [x,y,z]=q.front();
       q.pop_front();
               if(st[x][y][z]) continue;
       st[x][y][z]=true;
       //cout<<x<<" "<<y<<" "<<dist[x][y][z]<<"\n";
       int tx=x+dx[z],ty=y+dy[z];
       if(g[tx][ty]=='#'&&g[x][y]=='T'){
           cout<<dist[x][y][z];return ;
       }
       if(g[tx][ty]!='#')
       {
           if(st[tx][ty][z]) continue;
           dist[tx][ty][z]=dist[x][y][z];
           q.emplace_front(tx,ty,z);
           continue;
       }else{
           for(int i=0;i<4;i++){
               int tx=x+dx[i],ty=y+dy[i];
               if(tx<=0||ty<=0||tx>n||ty>m) continue;
               if(g[tx][ty]=='#') continue;
               if(st[tx][ty][i]) continue;
               dist[tx][ty][i]=dist[x][y][z]+1;
               q.emplace_back(tx,ty,i);
           }
       }
   }
   cout<<-1;
}
 signed main(){
    cin.tie(0);cout.tie(0);ios::sync_with_stdio(0);
    int t=1;
   // cin>>t;
    while(t--) solve();
    return 0;
}