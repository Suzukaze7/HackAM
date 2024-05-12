#include <bits/stdc++.h>
 typedef long long LL;
const int N = 1e5 + 10;
 LL f[N];
 int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
         for (int i = 1; i < N; i++) {
        f[i] += 1;
        for (int j = 2 * i; j < N; j += i) {
            f[j] += f[i];
        } 
    }
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        std::cin >> x;
        std::cout << f[x] << " \n"[i == n];
    }
         return 0;
}