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
 signed main() {
    IOS
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i: a) {
        cin >> i;
    }
    int res = accumulate(a.begin(), a.end(), 0);
    if (res % 2) {
        cout << -1 << endl;
    } else {
        int ans1 = 0, ans2 = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] % 2) {
                ans1++;
            } else {
                ans2++;
            }
        }
        cout << ans1 / 2 + ans2 << endl;
    }
    return 0;
}