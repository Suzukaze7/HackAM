#include <bits/stdc++.h>
 using namespace std;
 using vi = vector<int>;
 const int inf = 1e9;
const int dx[] = {0, 0, -1, 1} , dy[] = {1, -1, 0, 0};
  int main(){
    int n, m ;
    cin >> n >> m;
    vector<string> g(n);
    for(auto &i : g)
        cin >> i;
    int sx , sy, tx, ty;
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < m; j ++){
            if(g[i][j] == 'S') sx = i, sy = j;
            if(g[i][j] == 'T') tx = i, ty = j;
        }
    vector dis(n, vi(m, inf)), vis(n, vi(m));
    queue<pair<int,int>> q;
    q.emplace(sx, sy), dis[sx][sy] = 0;
    while(not q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if(vis[x][y])  continue;
        vis[x][y] = 1; 
        int d = dis[x][y];
        for(int i = 0, fx, fy , t; i < 4; i ++){
            fx = x, fy = y;
            while(0 <= fx+dx[i] and fx+dx[i] < n and 0 <= fy+dy[i] and fy+dy[i] < m){
                if(g[fx + dx[i]][fy + dy[i]] == '#') break;
                else fx += dx[i], fy += dy[i]; 
            }
            if(dis[fx][fy] <= d + 1) continue;
            dis[fx][fy] = d + 1;
            q.emplace(fx, fy);
        }
    }
    if(dis[tx][ty] == inf) cout << "-1\n";
    else cout << dis[tx][ty] << "\n";
    return 0;
}