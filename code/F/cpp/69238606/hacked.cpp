#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    int odd = 0, even = 0;
    for (int i = 1; i <= n; i++) {
        int d;
        std::cin >> d;
        if (d & 1) odd++;
        else even++;
    }
    
    if (odd & 1) {
        std::cout << -1 << '\n';
    } else {
        std::cout << even + odd / 2 << '\n';    
    }
    
    return 0;
}