#include <bits/stdc++.h>
// #define int long long
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int, int>
#define db double
using namespace std;
const int maxn = 2e5 + 10;
const int mod = 998244353;
int vis[maxn];
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        vis[(x - i + n) % n] = 1;
    }
    int p = 0;
    while (p < k && vis[p])
        p++;
    if (p == k)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
    // system("pause");
    return 0;
}