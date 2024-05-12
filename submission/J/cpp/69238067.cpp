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
    int res = accumulate(a.begin(), a.end(), -50);
    cout << max(0ll, res);
    return 0;
}