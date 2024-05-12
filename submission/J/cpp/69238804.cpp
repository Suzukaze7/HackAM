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
    int n;
    cin >> n;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        sum += x;
    }
    cout << max(0, sum - 50) << endl;
    // system("pause");
    return 0;
}