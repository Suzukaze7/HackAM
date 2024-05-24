#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    int s = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        std::cin >> x;
        s += x;
    }
    
    std::cout << std::max(0, s - 50) << '\n';
    
    return 0;
}