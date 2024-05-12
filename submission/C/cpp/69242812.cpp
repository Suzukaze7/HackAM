#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pii;
const int N = 2e5 + 10, mod = 1e9 + 7;
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 2);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        // cout << len << " " << len1 << "\n";
    }
    a[0] = a[n];
    a[n + 1] = a[1];
    vector<int> tmp;
    vector<int> tmp1;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] == i)
        {
            tmp.push_back(i);
        }
        if (a[i - 1] == i)
        {
            tmp1.push_back(i - 1);
        }
        if (a[i + 1] == i)
            tmp1.push_back(i + 1);
    }
    if (k == 1 && !tmp.empty())
    {
        cout << "Yes\n";
        return;
    }
     for (auto c : tmp)
    {
         for (auto v : tmp1)
        {
            // cout << c << " " << v << "\n";
            if (c != v)
            {
                cout << "Yes\n";
                return;
            }
        }
    }
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