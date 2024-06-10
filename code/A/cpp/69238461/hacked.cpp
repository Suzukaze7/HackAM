#include <bits/stdc++.h>

using namespace std;
#define IOS ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
#define int long long

# ifdef LOCAL

# include "C:\Program Files\DEBUG\debug.h"

# else
# define debug(...) 114514
# define ps 114514
# endif

const int inf = 1e12;
pair<int, int> d[4] = {{0,  1},
                       {0,  -1},
                       {1,  0},
                       {-1, 0}};

signed main() {
    IOS
    int n, m;
    cin >> n >> m;
    vector<vector<char>> mp(n + 1, vector<char>(m + 1, 0ll));
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, inf));

    int ans = inf;
    int fx, fy;
    queue<tuple<int, int, int>> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mp[i][j];
            if (mp[i][j] == 'S') {
                dp[i][j] = 0;
                for (int k = 0; k < 4; k++)
                    q.emplace(i, j, k);
            } else if (mp[i][j] == 'T') {
                fx = i;
                fy = j;
            }
        }
    }

    auto check = [&](int x, int y) {
        return (x >= 1 && x <= n && y >= 1 && y <= m && mp[x][y] != '#');
    };
    while (!q.empty()) {
        auto [x, y, dir] = q.front();
        q.pop();
        //  debug(x, y, dir);
        int nx = x + d[dir].first;
        int ny = y + d[dir].second;
        int tx = x, ty = y;
        while (check(nx, ny)) {
            tx = nx;
            ty = ny;
            nx = tx + d[dir].first;
            ny = ty + d[dir].second;
        }
        if (dp[x][y] + 1 < dp[tx][ty]) {
            dp[tx][ty] = dp[x][y] + 1;
            for (int i = 0; i < 4; i++) {
                q.emplace(tx, ty, i);
            }
        }
    }
    ans = min(ans, dp[fx][fy]);
    if (ans != inf)
        cout << ans << endl;
    else
        cout << -1 << endl;
    return 0;
}