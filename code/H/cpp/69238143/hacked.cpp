#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1e5 + 10, mod = 1e9 + 7;
int a[N];
void solve()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        int ans = 0;
        for (int j = 1; j * j <= x; j++)
        {
            if (x % j == 0)
            {
                if (x != j)
                    ans += a[j];
                if (x / j != j && x / j != x)
                    ans += a[x / j];
            }
        }
        cout << ans + 1 << ' ';
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int j = 1; j <= 1e5; j++)
    {
        int ans = 0;
        for (int i = 1; i * i <= j; i++)
        {
            if (j % i == 0)
            {
                if (j != i)
                    ans += a[i];
                if (j / i != i && j / i != j)
                    ans += a[j / i];
            }
        }
        a[j] = ++ans;
    }
    int t;
    t = 1;
    while (t--)
        solve();
    return 0;
}
