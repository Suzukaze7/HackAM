// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("tune=native")
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define endl "\n"
#define vi vector<int>
#define pii pair<int, int>
#define all(a) (a).begin(), (a).end()
#define Point pii
#define x first
#define y second
Point operator+(Point a, Point b) { return {a.x + b.x, a.y + b.y}; }
vector<Point> dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int Mod(int num, int mod) { return (num % mod + mod) % mod; }
inline int read()
{
    int f = 0, x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')
        f |= (ch == '-'), ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return f ? -x : x;
}
inline void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
 inline void vread(int n, vi &vec)
{
    for (int i = 0; i < n; i++)
        vec[i] = read();
}
inline void vwriteln(int n, vi &vec)
{
    for (int i = 0; i < n; i++)
        write(vec[i]), putchar(' ');
    putchar('\n');
}
#define SINGLE
vector<int> eiFilter(1e5 + 1, 1);
void init()
{
    for (int i = 1; i <= 1e5; i++)
    {
        for (int j = i + i; j <= 1e5; j += i)
            eiFilter[j] += eiFilter[i];
    }
}
void solve()
{
    init();
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int q;
        cin >> q;
        cout << eiFilter[q] << " ";
    }
}
 signed main()
{
    IOS;
    int t;
#ifdef SINGLE
    t = 1;
#else
    cin >> t;
#endif
    while (t--)
        solve();
    return 0;
}