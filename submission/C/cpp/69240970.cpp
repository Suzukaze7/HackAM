#include <bits/stdc++.h>
 int main() {
     std::ios::sync_with_stdio(false);
     std::cin.tie(nullptr);
           int n, k;
     std::cin >> n >> k;
           std::vector<int> a(n + 1);
           for (int i = 1; i <= n; i++) {
         std::cin >> a[i];
     }
           int c1 = 0;
     for (int i = 1; i <= n; i++) {
         if (a[i] == i) c1++;
     }
     for (int i = 1; i < n; i++) {
         std::swap(a[i], a[i + 1]);
     }
     int c2 = 0 ;
     for (int i = 1; i <= n; i++) {
         if (a[i] == i) c2++;
     }
     for (int i = n; i > 1; i--) {
         std::swap(a[i], a[i - 1]);
     }
     for (int i = n; i > 1; i--) {
         std::swap(a[i], a[i - 1]);
     }
     int c3 = 0;
     for (int i = 1; i <= n; i++) {
         if (a[i] == i) c3++;
     }
           if (!c1 || (k > 1 && !c2 && !c3)) {
         std::cout << "No\n";
     } else {
         std::cout << "Yes\n";
     }
           return 0;
 }