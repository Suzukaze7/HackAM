#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
const int N = 1e3 + 10;
int n,m;
char s[N][N];
int sx,sy,ex,ey;
int ans = 1e9;
int cnt = 0;
int st[N][N];
int dx[] = {0,0,-1,1},dy[] = {1,-1,0,0};
int dist[N][N];
map<pair<int,int>,pair<int,int>> mp;
void bfs(){
    queue<pair<int,int>> q;
    q.push({sx,sy});
    memset(dist,0x3f,sizeof dist);
    dist[sx][sy] = 0;
    while(q.size()){
        auto t = q.front();
        q.pop();
        st[t.x][t.y] = 1;
        for(int i = 0; i < 4; i ++){
            int xx = t.x,yy = t.y;
            int z = 1;
            while(s[xx + dx[i] * z][yy + dy[i] * z] != '#'){
                z ++;
            }
            if(z != 1) z--;
            xx = xx + dx[i] * z,yy = yy + dy[i] * z;
            if(s[xx][yy] == '#' || st[xx][yy]) continue;
            if(dist[xx][yy] > dist[t.x][t.y] + 1){
                dist[xx][yy] = dist[t.x][t.y] + 1;
                mp[{xx,yy}] = {t.x,t.y};
                q.push({xx,yy});
                st[xx][yy] = 1;
            }
            if(s[xx][yy] == 'T') return ;
        }
    }
}
int main(){
    cin >> n >> m;
    for(int i = 1;i <= n;i ++){
        for(int j = 1; j <= m; j ++){
            cin >> s[i][j];
            if(s[i][j] == 'S') sx = i,sy = j;
            if(s[i][j] == 'T') ex = i,ey = j;
        }
    }
    bfs();
    if(dist[ex][ey] == 0x3f3f3f3f) cout << -1;
    else{
        cout << dist[ex][ey];
    }
    return 0;
}