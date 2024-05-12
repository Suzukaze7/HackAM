#include <bits/stdc++.h>
 #define int long long
using namespace std;
  void solve() {
    int n,m;cin>>n>>m;
    vector g(n+1,vector(m+1,'.'));
    vector dis(n+1,vector(m+1,(int)1e9));
    vector l(n+1,vector(m+1,0ll)),r(n+1,vector(m+1,0ll)),u(n+1,vector(m+1,0ll)),d(n+1,vector(m+1,0ll));
    int x,y,ex,ey;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>g[i][j];
            if(g[i][j]=='S') x=i,y=j;
            if(g[i][j]=='T') ex=i,ey=j;
            if(g[i][j]=='#') l[i][j]=j,u[i][j]=i;
            else l[i][j]=l[i][j-1],u[i][j]=u[i-1][j];
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=m;j>=1;j--){
            if(g[i][j]=='#') r[i][j]=j,d[i][j]=i;
            else r[i][j]=r[i][j+1],d[i][j]=d[i+1][j];
        }
    }
    queue<tuple<int,int,int>> q;
    q.emplace(x,y,0);
    dis[x][y]=0;
    while(!q.empty()){
        auto [r1,c1,step]=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            if(i==0){
                int nr=r1,nc=r[r1][c1]-1;
                if(dis[nr][nc]>step){
                    dis[nr][nc]=step+1;
                    q.emplace(nr,nc,step+1);
                }
            }else if(i==1){
                int nr=r1,nc=l[r1][c1]+1;
                if(dis[nr][nc]>step){
                    dis[nr][nc]=step+1;
                    q.emplace(nr,nc,step+1);
                }
            }else if(i==2){
                int nr=u[r1][c1]+1,nc=c1;
                if(dis[nr][nc]>step){
                    dis[nr][nc]=step+1;
                    q.emplace(nr,nc,step+1);
                }
            }else{
                int nr=d[r1][c1]-1,nc=c1;
                if(dis[nr][nc]>step){
                    dis[nr][nc]=step+1;
                    q.emplace(nr,nc,step+1);
                }
            }
        }
    }
    cout<<(dis[ex][ey]>=1e9?-1:dis[ex][ey]);
}
 signed main() {
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
    int t = 1;//std::cin >> t;
    while (t--) solve();
    return 0;
}