#include <bits/stdc++.h>
// #define int long long
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int, int>
#define db double
using namespace std;
const int maxn = 1e5 + 10;
const int mod = 998244353;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, cntji = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cntji += x & 1;
    }
    if (cntji & 1) {
        cout << -1 << endl;
    } else {
        cout << cntji / 2 + (n - cntji) << endl;
    }
    // system("pause");
    return 0;
}