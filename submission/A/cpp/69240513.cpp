#include <bits/stdc++.h>
// #define int long long
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int, int>
#define db double
using namespace std;
const int maxn = 1e3 + 10;
const int mod = 998244353;
char ch[maxn][maxn];
pii nxt[maxn][maxn][4];
int vis[maxn][maxn];
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    memset(vis, -1, sizeof(vis));
    pii s, t;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= m + 1; j++)
            ch[i][j] = '#';
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cin >> ch[i][j];
            if (ch[i][j] == 'S')
                s = pii(i, j);
            else if (ch[i][j] == 'T')
                t = pii(i, j);
            for (int k = 0; k < 4; k++)
                nxt[i][j][k] = pii(i, j);
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (ch[i][j] != '#') {
                if (ch[i][j - 1] == '#')
                    nxt[i][j][0] = pii(i, j);
                else
                    nxt[i][j][0] = nxt[i][j - 1][0];
                if (ch[i - 1][j] == '#')
                    nxt[i][j][2] = pii(i, j);
                else
                    nxt[i][j][2] = nxt[i - 1][j][2];
            }
        }
    for (int i = n; i; i--)
        for (int j = m; j; j--) {
            if (ch[i][j + 1] == '#')
                nxt[i][j][1] = pii(i, j);
            else
                nxt[i][j][1] = nxt[i][j + 1][1];
            if (ch[i + 1][j] == '#')
                nxt[i][j][3] = pii(i, j);
            else
                nxt[i][j][3] = nxt[i + 1][j][3];
        }
    queue<pii> q;
    vis[s.first][s.second] = 0;
    q.push(s);
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int xx = nxt[x][y][i].first, yy = nxt[x][y][i].second;
            if (vis[xx][yy] == -1) {
                vis[xx][yy] = vis[x][y] + 1;
                q.push(pii(xx, yy));
            }
        }
    }
    cout << vis[t.first][t.second] << endl;
    // system("pause");
    return 0;
}