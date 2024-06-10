#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::list<int> List;
    
    std::vector<std::string> str(n + 1);
    
    for (int i = 1; i <= n; i++) {
        std::cin >> str[i];
        List.push_back(i);
    }
    
    std::vector<bool> st(n + 1, false);
    
    auto it = List.begin();
    int cnt = 0;
    while (m--) {
        std::string t;
        std::cin >> t;
        if (it == List.end()) break;
        if (t == str[*it]) {
            if (cnt == 0) st[*it] = true, it = List.erase(it);
            else cnt = 0, it++;
        } else {
            cnt++;
        }
        if (it == List.end()) it = List.begin();
    }
    
    for (int i = 1; i <= n; i++) {
        if (st[i]) std::cout << str[i] << '\n';
    }
    
    return 0;
}