#include <bits/stdc++.h>
 int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
         int n, m, v;
    std::cin >> n >> m >> v;
         std::vector<int> vi(n + 1);
         for (int i = 1; i <= n; i++) {
        std::cin >> vi[i];
    }
         std::sort(vi.begin() + 1, vi.end());
         std::vector<int> dp(v + 1, -1e9);
    dp[0] = 0;
         int ans = -1;
    for (int i = 1; i <= n; i++) {
        std::vector<int> ndp = dp;
        //考虑选
        for (int j = vi[i]; j <= v; j++) {
            ndp[j] = std::max(ndp[j], dp[j - vi[i]] + 1);
            if (j == v) {
                if (dp[j - vi[i]] >= 0) {
                    ans = std::max(ans, dp[j - vi[i]] + m * vi[i] + 1);
                }
            }
        }
        dp.swap(ndp);
    }
    std::cout << ans << '\n';
         return 0;
}