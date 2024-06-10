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

const int N = 1e5 + 1;

signed main() {
    IOS
    int n;
    cin >> n;
    vector<int> dp(100100, 0);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= (int) sqrt(i); j++) {
            if (i % j == 0) {
                dp[i] += dp[j];
                if (j != 1 && j * j != i) {
                    dp[i] += dp[i / j];
                }
            }
        }
        dp[i]++;
    }
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cout << dp[x] << " ";
    }
    return 0;
}