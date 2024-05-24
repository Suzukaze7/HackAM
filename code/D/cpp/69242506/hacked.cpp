#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pii;
const int N = 2e5 + 10, mod = 1e9 + 7;
int cnt[N];
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        int len = 0;
        if (i < a[i])
        {
            len = a[i] - i;
        }
        else if (i > a[i])
        {
            len = n - i + a[i];
        }
        // cout << len << " ";
        cnt[len]++;
    }

    int ans = -1;
    for (int i = 0; i < n; i++)
    {
        if (cnt[i])
            continue;
        else
        {
            ans = i;
            break;
        }
    }
    if (ans == -1)
        ans = n;
    // cout << ans << "\n";
    if (ans >= k)
        cout << "Yes\n";
    else
        cout << "No\n";
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
