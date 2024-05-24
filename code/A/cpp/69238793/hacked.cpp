#include <bits/stdc++.h>

const int N = 1010;
char s[N][N];
int d[N][N];
int left[N][N], right[N][N], down[N][N], up[N][N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    int sx, sy, ex, ey;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> s[i][j];
            if (s[i][j] == 'S') sx = i, sy = j;
            if (s[i][j] == 'T') ex = i, ey = j;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == '#') left[i][j] = j;
            else left[i][j] = left[i][j - 1];
        }
        for (int j = m; j >= 1; j--) {
            if (s[i][j] == '#') right[i][j] = j;
            else right[i][j] = right[i][j + 1];
        }
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[j][i] == '#') up[i][j] = j;
            else up[i][j] = up[i][j - 1];
        }
        for (int j = n; j >= 1; j--) {
            if (s[j][i] == '#') down[i][j] = j;
            else down[i][j] = down[i][j + 1];
        }
    }
    
    memset(d, -1, sizeof d);
    
    d[sx][sy] = 0;
    std::queue<std::pair<int, int>> q;
    q.push({sx, sy});
    
    while (q.size()) {
        auto [x, y] = q.front();
        q.pop();
        int ry = right[x][y] - 1;
        if (d[x][ry] == -1) {
            d[x][ry] = d[x][y] + 1;
            q.push({x, ry});
        }
        int ly = left[x][y] + 1;
        if (d[x][ly] == -1) {
            d[x][ly] = d[x][y] + 1;
            q.push({x, ly});
        }
        int ux = up[y][x] + 1;
        if (d[ux][y] == -1) {
            d[ux][y] = d[x][y] + 1;
            q.push({ux, y});
        }
        int dx = down[y][x] - 1;
        if (d[dx][y] == -1) {
            d[dx][y] = d[x][y] + 1;
            q.push({dx, y});
        }
    }
    
    std::cout << d[ex][ey] << '\n';
    
    return 0;
}