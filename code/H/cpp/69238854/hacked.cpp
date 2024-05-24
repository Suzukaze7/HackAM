#include <bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int, int>
#define db double
using namespace std;
const int maxn = 1e5 + 10;
const int mod = 998244353;
int f[maxn];
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    for (int i = 1; i <= 1e5; i++)
        for (int j = 2 * i; j <= 1e5; j += i)
            f[j] += f[i] + 1;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cout << f[x] + 1 << " ";
    }
    // system("pause");
    return 0;
}