#include <bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int, int>
#define db double
using namespace std;
const int maxn = 1e5 + 10;
const int mod = 998244353;
int v[maxn];
int dp[maxn];
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    int n, m, V;
    cin >> n >> m >> V;
    for (int i = 1; i <= n; i++)
        cin >> v[i];
    sort(v + 1, v + 1 + n);
    int ans = -1;
    for (int i = 1; i <= n; i++) {
        if (V - v[i] >= 0 && dp[V - v[i]] != -1)
            ans = max(ans, dp[V - v[i]] + 1 + m * v[i]);
        for (int j = V; j >= v[i]; j--)
            if (dp[j - v[i]] != -1)
                dp[j] = max(dp[j], dp[j - v[i]] + 1);
    }
    cout << ans << endl;
    // system("pause");
    return 0;
}