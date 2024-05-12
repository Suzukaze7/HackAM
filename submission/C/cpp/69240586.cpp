#include <bits/stdc++.h>
// #define int long long
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int, int>
#define db double
using namespace std;
const int maxn = 2e5 + 10;
const int mod = 998244353;
int arr[maxn], vis1[maxn], vis2[maxn];
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];
    for (int i = 1; i <= n; i++) {
        int x = arr[i];
        vis1[(x - i + n) % n] = 1;
        vis2[(i - x + n) % n] = 1;
    }
    int p = 0, ok = 0;
    while (p < k && vis1[p]) {
        p++;
        if (vis2[p])
            ok = 1;
    }
    if (p == k)
        ok = 1;
    p = 0;
    while (p < k && vis2[p]) {
        p++;
        if (vis1[p])
            ok = 1;
    }
    if (p == k)
        ok = 1;
    cout << (ok ? "Yes" : "No") << endl;
    // system("pause");
    return 0;
}