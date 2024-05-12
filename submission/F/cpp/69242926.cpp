#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define int long long
const int N = 1e5 + 10, mod = 1e9 + 7;
 void solve()
{
    int n;
    cin >> n;
    int c0 = 0, c1 = 0, c2 = 0;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        if (!x)
            c0++;
        else if (x & 1)
            c1++;
        else
            c2++;
    }
    int ans = 0;
    if (c1 & 1)
    {
        cout << -1 << '\n';
        return;
    }
    ans += c0;
    ans += c2 + c1 / 2;
    cout << ans;
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