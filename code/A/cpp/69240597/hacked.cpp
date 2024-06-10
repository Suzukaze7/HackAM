#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1010, mod = 1e9 + 7;
bool st[N][N];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
void solve()
{
    int n, m;
    cin >> n >> m;
    string s[n];
    int x1, y1, x2, y2;
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        for (int j = 0; j < m; j++)
        {
            if (s[i][j] == 'S')
            {
                x1 = i;
                y1 = j;
            }
            if (s[i][j] == 'T')
            {
                // cout << i << " " << j << '\n';
                x2 = i;
                y2 = j;
            }
        }
    }
    auto check = [&](tuple<int, int, int> q, int i)
    {
        auto [x, y, w] = q;
        tuple<int, int, int> tmp = {-1, -1, -1};
        while (x >= 0 && x < n && y >= 0 && y < m && s[x][y] != '#')
        {
            x += dx[i];
            y += dy[i];
            if (s[x][y] == '#' && !st[x - dx[i]][y - dy[i]] && s[x - dx[i]][y - dy[i]] != '#')
            {
                tmp = {x - dx[i], y - dy[i], 0};
                return tmp;
            }
        }
        return tmp;
    };
    queue<tuple<int, int, int>> q;
    q.push({x1, y1, 0});
    int ans = 1e9;
    while (q.size())
    {
        auto t = q.front();
        auto [xx, yy, w] = q.front();
        q.pop();
        if (st[xx][yy])
            continue;
        st[xx][yy] = 1;
        // cout << xx << " " << yy << "\n";
        for (int i = 0; i < 4; i++)
        {
            auto [x, y, z] = check(t, i);
            if (x != -1)
            {
                z = w + 1;
                if (x == x2 && y == y2)
                {
                    ans = min(ans, z);
                }
                q.push({x, y, z});
            }
        }
        // cout << xx << " " << yy <<" "<<w<< '\n';
    }
    if (ans == 1e9)
        cout << -1 << "\n";
    else
        cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    t = 1;
    while (t--)
        solve();
    return 0;
}
