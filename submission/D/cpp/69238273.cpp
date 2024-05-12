#include <bits/stdc++.h>
 int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
         int n, k;
    std::cin >> n >> k;
         std::vector<int> f(n + 1, 0);
         for (int i = 1; i <= n; i++) {
        int x;
        std::cin >> x;
        f[((x - i) % n + n) % n]++;
    }
         int ans = 0;
    while (f[ans]) ans++;
         std::cout << (ans >= k ? "Yes" : "No") << '\n';
         return 0;
}