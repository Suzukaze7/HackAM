//#pragma GCC optimize(2)
 #include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include<stack>
#include<cmath>
#include <unordered_set>
#include <unordered_map>
#include<set>
#include <map>
#include<ctime>
#include<bitset>
 using namespace std;
 typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int>PII;
 #define fi first
#define se second
#define ls u<<1
#define rs u<<1|1
#define all(ss) ss.begin(),ss.end()
#define pb push_back
  int const mod=1e9+7; 
int const B=507;
//int const mod=998244353; 
//int const base=131,mod=2e9+11;
int const N=1007,M=2e6+7;
int const INF=0x3f3f3f3f;
LL const INFF=0x3f3f3f3f3f3f3f3f;
 int n,m,q,k;
char s[N][N];
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
bool vis[N][N];
struct Node{
    int x,y,step;
};
 int bfs(){
    int sx,sy,tx,ty;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i][j]=='S')    sx=i,sy=j;
            else if(s[i][j]=='T')   tx=i,ty=j;
        }
    }
//  cout<<sx<<" "<<sy<<endl;
//  cout<<tx<<" "<<ty<<endl;
         queue<Node>q; q.push({sx,sy,1});
    while(q.size()){
        Node t=q.front(); q.pop();  
        int x=t.x,y=t.y;
        if(vis[x][y])   continue;
        vis[x][y]=true;
//      cout<<x<<" "<<y<<endl;
        for(int i=0;i<4;i++){
            for(int c=1;;c++){
                int bx=x+c*dx[i],by=y+c*dy[i];
                if(s[bx][by]=='#'){
                    if(c!=1){   //最少移动了一次
                        bx=x+(c-1)*dx[i],by=y+(c-1)*dy[i];
                        if(bx==tx&&by==ty)  return t.step;  //注意是只能婷在那里，中途经过不算
                        if(!vis[bx][by]) q.push({bx,by,t.step+1});
                    }
                    break;
                }
            }
        }
    }
         return -1;
}
/*
4 4
####
#ST#
##.#
####
  7 7
#######
#S...##
##.#.##
##....#
#T..#.#
#.....#
#######
*/
 void solve(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)    scanf("%s",s[i]+1);
//    for(int i=1;i<=n;i++)  cout<<s[i]+1<<endl;
    cout<<bfs();
} 
  void init(){
     }
 int main()
{
    //std::ios::sync_with_stdio(false);   cin.tie(0); cout.tie(0);
    //init();
    int T=1;
    //cin>>T;
//    scanf("%d",&T);
         for(int i=1;i<=T;i++){
        solve();
    }
         return 0;
}