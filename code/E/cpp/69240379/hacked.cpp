#include <bits/stdc++.h>
// #define int long long
#define inf 0x3f3f3f3f
#define ll long long
#define pii pair<int, int>
#define db double
using namespace std;
const int maxn = 2e5 + 10;
const int mod = 998244353;
string str[maxn];
int vis[maxn], pre[maxn], nxt[maxn];
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    set<int> s;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> str[i];
    for (int i = 0; i < n; i++) {
        pre[i] = (i - 1 + n) % n;
        nxt[i] = (i + 1) % n;
    }
    int p = 0;
    for (int i = 1; i <= m; i++) {
        string tem;
        cin >> tem;
        vis[p]++;
        if (str[p] == tem) {
            if (vis[p] == 1) {
                s.insert(p);
                pre[nxt[p]] = pre[p];
                nxt[pre[p]] = nxt[p];
            }
            p = nxt[p];
            vis[p] = 0;
        }
    }
    for (auto it : s)
        cout << str[it] << endl;
    // system("pause");
    return 0;
}